
foreach ($Arch in @('x64', 'arm64')) {
    New-Item -Type Directory -Path "idl/$Arch" -ErrorAction SilentlyContinue
    Copy-Item ./idl/ms-dtyp.h ./idl/$Arch/ms-dtyp.h -Force

    foreach ($ModuleName in @('SessEnvRpc', 'rcmpublic', 'tspubrpc', 'TSVIPRpc')) {
        midl.exe "./idl/$ModuleName.idl" /I idl /notlb /header "$ModuleName.h" /env $Arch /server none /out "./idl/$Arch"
        
        $stubFile = "idl/${Arch}/${ModuleName}_c.c"
        if (Test-Path $stubFile) {
            (Get-Content $stubFile) | ForEach-Object {
                $_ -replace '^(VOID\s+Opnum\d+NotUsedOnWire)', 'static $1'
            } | Set-Content $stubFile
        }
    }
}
