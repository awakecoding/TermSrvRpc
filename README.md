# TermSrvRpc

An implementation of the Terminal Services Terminal Server Runtime Interface Protocol (MS-TSTS) RPC calls, made usable from .NET through pinvoke.

## Building

Enter a Visual Studio shell:

```powershell
Install-Module VsDevShell
Enter-VsDevShell
```

Run the script to generate the RPC native code using the midl compiler:

```powershell
.\rpcgen.ps1
```

Generate the CMake project and build it:

```powershell
mkdir build-x64 && cd build-x64
cmake -G "Visual Studio 17 2022" -A x64 ..
cmake --build . --config Release
```

## Random Notes

[MS-TSTS]: Terminal Services Terminal Server Runtime Interface Protocol

tsallproc.h
tsdef.h
winsta.h
tspubrpc.idl
RCMPublic.idl
TSVIPRpc.idl
legacy.idl

LSM Session (tspubrpc.idl)<4>
{ 484809d6-4239-471b-b5bc-61df8c23ac48 }
\PIPE\LSM_API_service
\PIPE\UNIFIED_API_service<5>

LSM Notification (tspubrpc.idl)<6>
{ 11899a43-2b68-4a76-92e3-a3d6ad8c26ce }
\PIPE\LSM_API_service
\PIPE\UNIFIED_API_service<7>

LSM Enumeration (tspubrpc.idl)<8>
{ 88143fd0-c28d-4b2b-8fef-8d882f6a9390 }
\PIPE\LSM_API_service
\PIPE\UNIFIED_API_service<9>

TermSrv (RCMPublic.idl)<10>
{ bde95fdf-eee0-45de-9e12-e5a61cd0d4fe }
\PIPE\TermSrv_API_service

TermSrv Listener (RCMPublic.idl)<11>
{ 497d95a6-2d27-4bf5-9bbd-a6046957133c }
\PIPE\TermSrv_API_service

Legacy (Legacy.idl)
{ 5ca4a760-ebb1-11cf-8611-00a0245420ed }
\PIPE\Ctx_WinStation_API_service

TSVIPPublic (TSVIPRpc.idl)
{53b46b02-c73b-4a3e-8dee-b16b80672fc0}
\PIPE\TSVIP_Service

SessEnvPublicRpc (SessEnvRpc.idl)
{1257B580-CE2F-4109-82D6-A9459D0BF6BC}
\PIPE\SessEnvPublicRpc
