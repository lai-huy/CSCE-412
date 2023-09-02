Invoke-WebRequest -Uri "https://download.oracle.com/java/17/latest/jdk-17_windows-x64_bin.msi" -OutFile "./java.exe"
Invoke-WebRequest -Uri "https://github.com/git-for-windows/git/releases/download/v2.42.0.windows.2/Git-2.42.0.2-64-bit.exe" -OutFile "./git.exe"
Invoke-WebRequest -Uri "https://github.com/vim/vim-win32-installer/releases/download/v9.0.1839/gvim_9.0.1839_x64.exe" -Outfile "./vim.exe"

Start-Process -FilePath "./java.exe" -ArgumentList '/S' -Wait
Start-Process -FilePath "./git.exe" -ArgumentList '/S' -Wait
Start-Process -FilePath "./vim.exe" -ArgumentList '/S' -Wait