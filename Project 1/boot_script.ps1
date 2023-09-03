<powershell>
$loc = "c:\Users\Administrator\Desktop\debug.log"

Write-Output "Starting Script" >> $loc

Invoke-Expression ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))

Write-Output "Installing VS Code" >> $loc
choco install -y vscode --force --force-dependencies --verbose >> $loc

Write-Output "Installing Git" >> $loc
choco install -y git --force --force-dependencies --verbose >> $loc

Write-Output "Installing Java" >> $loc
choco install -y openjdk --force --force-dependencies --verbose >> $loc

Write-Output "Install PDF Reader" >> $loc
choco install -y adobereader --force --force-dependencies --verbose >> $loc

Write-Output "Completed" >> $loc
</powershell>
<persist>false</persist>