
$PredefExtra = '
#include <stdlib.h>
static void* MIDL_user_allocate(size_t sz) { return malloc(sz); }
static void MIDL_user_free(void* ptr) { free(ptr); }'

foreach ($Arch in @('x64', 'arm64')) {
    New-Item -Type Directory -Path "idl/$Arch" -ErrorAction SilentlyContinue
    Copy-Item ./idl/ms-dtyp.h ./idl/$Arch/ms-dtyp.h -Force

    foreach ($ModuleName in @('SessEnvRpc')) {
        midl.exe "./idl/$ModuleName.idl" /I idl /notlb /header "$ModuleName.h" /env $Arch /server none /out "./idl/$Arch"
        $ClientStub = Get-Content -Path "./idl/$Arch/${ModuleName}_c.c" -Raw
        $ClientStub = $PredefExtra + $ClientStub
        Set-Content -Path "./idl/$Arch/${ModuleName}_c.c" -Value $ClientStub
    }
}
