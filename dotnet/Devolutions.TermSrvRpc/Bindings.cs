using System;
using System.Net.NetworkInformation;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace Devolutions.TermSrvRpc
{
    public static class Bindings
    {
        public enum SHADOW_CONTROL_REQUEST
        {
            SHADOW_CONTROL_REQUEST_VIEW = 0,
            SHADOW_CONTROL_REQUEST_TAKECONTROL = 1
        }

        public enum SHADOW_PERMISSION_REQUEST
        {
            SHADOW_PERMISSION_REQUEST_SILENT = 0,
            SHADOW_PERMISSION_REQUEST_REQUESTPERMISSION = 1
        }

        public enum SHADOW_REQUEST_RESPONSE
        {
            SHADOW_REQUEST_RESPONSE_ALLOW = 0,
            SHADOW_REQUEST_RESPONSE_DECLINE = 1,
            SHADOW_REQUEST_RESPONSE_POLICY_PERMISSION_REQUIRED = 2,
            SHADOW_REQUEST_RESPONSE_POLICY_DISABLED = 3,
            SHADOW_REQUEST_RESPONSE_POLICY_VIEW_ONLY = 4,
            SHADOW_REQUEST_RESPONSE_POLICY_VIEW_ONLY_PERMISSION_REQUIRED = 5,
            SHADOW_REQUEST_RESPONSE_SESSION_ALREADY_CONTROLLED = 6
        }

        public static string SESSENVPUBLICRPC_ENDPOINT = "\\pipe\\SessEnvPublicRpc";
        public static string SESSENVPUBLICRPC_PROTOCOL_SEQUENCE = "ncacn_np";

        [DllImport("TermSrvRpc.dll")]
        public static extern uint RpcShadow2(
            IntPtr hBinding,
            ulong TargetSessionId,
            SHADOW_CONTROL_REQUEST eRequestControl,
            SHADOW_PERMISSION_REQUEST eRequestPermission,
            ref SHADOW_REQUEST_RESPONSE pePermission,
            IntPtr pszInvitation,
            ulong cchInvitation);
    }
}
