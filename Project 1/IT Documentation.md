<p align="center">
    <picture>
        <source media="(prefers-color-scheme: dark)" srcset="logo_dark.png">
        <source media="(prefers-color-scheme: light)" srcset="logo_light.png">
        <img alt="TAMU Department of Computer Science and Engineering" src="logo_dark.png">
    </picture>
</p>

# Creating the Environment
The Virtual Machine was created using Amazon Web Service's Lightsail framework using the Windows Server 2019.  
<img src="https://cdn.worldvectorlogo.com/logos/amazon-lightsail.svg" alt="AWS Lightsail" width=128px>

## Steps to Create the Environment
1. Create a new AWS Account or sign into an existing one.
2. Navigate to AWS Lightsail or click this [link](https://lightsail.aws.amazon.com/ls/webapp/home/instances).
3. Create a new instance of a virtual machine by clicking on the "Create Instance" button
4. Select the prefered location of the instance.
5. Select Microsoft Windows as the platform.
6. Select Windows Server 2019 as the blueprint from the "OS Only" option.
7. In the optional settings, include the following code in the `Launch Script` section.
```bash
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
```
8. Select an adequate instance plan for memory, processing, storange and transfer.
9. Alter the names as desired. Here is where you can scale deployment to as many virtual machines as needed.
10. Click on the "Create Instance" button.
11. Booting and instalization of the programs will take a few minutes.
