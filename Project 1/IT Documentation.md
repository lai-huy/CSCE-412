<p align="center">
    <picture>
        <source media="(prefers-color-scheme: dark)" srcset="logo_dark.png">
        <source media="(prefers-color-scheme: light)" srcset="logo_light.png">
        <img alt="TAMU Department of Computer Science and Engineering" src="logo_dark.png">
    </picture>
</p>

# Information Technology Documentation
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

## Justificiation of Pre-installed Software
Every instance of the Virtual Machine should come preinstalled with the following programs:
- Visual Studio Code
- Git
- Java
- Adobe Acrobat Reader

This part of the document will go over why these programs specifically are included

### Visual Studio Code
- **Devlopment Environment:** VS Code is a popular, lightweight code editor that supports a wide range of programming languages.
- **Productivity:** Developers often rely on VS Code extensions for tasks like debugging, code version control, and project management.

### Git
- **Version Control:** Git is a fundamental tool for version control in software development.
- **Seamless Integration:** Many development workflows depend on Git, so having it ready+ to use without manual installation simplifies the setup process.

### Java
- **Cross-Platform Development:** Java is a widely used, cross-platform programming language. Preinstalling Java enables users to run Java applications, applets, and development environments without dealing with Java installation and configuration.
- **Compatibility:** Many software applications, tools, and services rely on Java, making it a useful component for a virtual machine's versatility.

### Adobe Acrobat Reader
- **Document Viewing:** Users can easily open and view PDF documents, which are commonly used for documentation and information sharing.
- **User Convenience:** PDF files are ubiquitous in various domains, and not everyone has an alternative PDF viewer installed. 