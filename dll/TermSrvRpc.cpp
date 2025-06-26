#include "TermSrvRpc.h"

#include "rpc.h"
#include "rpcndr.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strsafe.h>

BOOL PrepareServerSPN(IN LPCWSTR pszNetworkAddress, __deref_out_opt LPWSTR* ppwszServerSPN) {
	LPWSTR pszTemplate = L"host/%s";
	*ppwszServerSPN = NULL;
	HRESULT hr = S_OK;
	UINT stringLength = wcslen(pszTemplate)+wcslen(pszNetworkAddress)+1;
	*ppwszServerSPN = (LPWSTR)LocalAlloc(LPTR, stringLength * sizeof(WCHAR));
	
	if (*ppwszServerSPN) {
		hr = StringCchPrintf(*ppwszServerSPN, stringLength, pszTemplate, pszNetworkAddress);
	}
	
	if (FAILED(hr)) {
		if (NULL != *ppwszServerSPN) {
			LocalFree(*ppwszServerSPN);
			*ppwszServerSPN = NULL;
		} 
	}
	
	return SUCCEEDED(hr);
}

RPC_STATUS TermSrvBind(IN LPCWSTR pszUuid, IN LPCWSTR pszProtocolSequence, IN LPCWSTR pszNetworkAddress, IN LPCWSTR pszEndPoint, IN LPCWSTR pszOptions, OUT RPC_BINDING_HANDLE *pHandle)
{
	RPC_STATUS Status;
	LPWSTR pszString = NULL;
	
	Status = RpcStringBindingComposeW((RPC_WSTR)pszUuid, (RPC_WSTR)pszProtocolSequence, (RPC_WSTR)pszNetworkAddress, (RPC_WSTR)pszEndPoint, (RPC_WSTR)pszOptions, (RPC_WSTR*) &pszString);
	
	if( Status != RPC_S_OK ) {
		wprintf ( L"Error %d in RpcStringBindingCompose", Status );
		goto TS_EXIT_POINT;
	}
	
	Status = RpcBindingFromStringBindingW((RPC_WSTR) pszString, pHandle);
	
	if (Status != RPC_S_OK) {
		wprintf(L"Error %d in RpcBindingFromStringBinding", Status);
		goto TS_EXIT_POINT;
	}

TS_EXIT_POINT:
	if (NULL != pszString) {
		RpcStringFreeW((RPC_WSTR*) &pszString);
	}
	return(Status);
}

RPC_STATUS TermSrvBindSecure(LPCWSTR pszUuid, LPCWSTR pszProtocolSequence, LPCWSTR pszNetworkAddress, LPCWSTR pszEndPoint, LPCWSTR pszOptions, RPC_BINDING_HANDLE* pHandle)
{
	RPC_STATUS Status;
	RPC_SECURITY_QOS qos;
	LPWSTR wszServerSPN = NULL;
	
	*pHandle = NULL;
	Status = TermSrvBind(pszUuid, pszProtocolSequence, pszNetworkAddress, pszEndPoint, pszOptions, pHandle);
	
	if (Status != RPC_S_OK) {
		wprintf(L"Error %d in TermSrvBind", Status);
		goto TS_EXIT_POINT;
	}
	
	qos.Capabilities = RPC_C_QOS_CAPABILITIES_MUTUAL_AUTH;
	qos.IdentityTracking = RPC_C_QOS_IDENTITY_DYNAMIC;
	qos.ImpersonationType = RPC_C_IMP_LEVEL_IMPERSONATE;
	qos.Version = RPC_C_SECURITY_QOS_VERSION;

	if (PrepareServerSPN(pszNetworkAddress, &wszServerSPN)) {
		Status = RpcBindingSetAuthInfoExW(*pHandle, (RPC_WSTR)wszServerSPN, RPC_C_AUTHN_LEVEL_PKT_PRIVACY, RPC_C_AUTHN_GSS_NEGOTIATE, NULL, RPC_C_AUTHZ_NAME, &qos);
		LocalFree(wszServerSPN);
	}
	else
	{
		Status = RpcBindingSetAuthInfoExW(*pHandle, (RPC_WSTR)pszNetworkAddress, RPC_C_AUTHN_LEVEL_PKT_PRIVACY, RPC_C_AUTHN_GSS_NEGOTIATE, NULL, RPC_C_AUTHZ_NAME, &qos);
	}
	
	if (RPC_S_OK != Status) {
		wprintf(L"Error %d in RpcBindingSetAuthInfoEx", Status);
		goto TS_EXIT_POINT;
	}

TS_EXIT_POINT:
	if (RPC_S_OK != Status && NULL != *pHandle) {
		RpcBindingFree(pHandle);
	} return Status;
}
