![TAMU Department of Computer Science and Engineering](logo.png)

# Using the Environment

The Virtual Machine comes preinstalled with the following programs:

<img src="https://upload.wikimedia.org/wikipedia/commons/9/9a/Visual_Studio_Code_1.35_icon.svg" alt="Visual Studio Code" width=128px>
<img src="https://git-scm.com/images/logos/downloads/Git-Icon-1788C.svg" alt="Git" width=128px>
<img src="https://www.vectorlogo.zone/logos/java/java-icon.svg" alt="Java v20.02" width=128px>
<img src="https://upload.wikimedia.org/wikipedia/commons/6/60/Adobe_Acrobat_Reader_icon_%282020%29.svg" alt="Adobe Acrobat Reader" width=128px>

## Connected to the Virtual Machine
These instructions assume that you are using a Windows Machine. If you are not, contact your manager to request access to a Windows Machine.

1. Open the Windows menu, and then search for `Remote Desktop Connection` or `RDC`.
2. Choose **Remote Desktop Connection** in the search results
![Remote Desktop Connection in the Start Menu](<rdc start menu.png>)
3. In the Computer text box, enter your Windows instance’s public IP address. The IP address will be given to you by your Manager.  
![Remote Desktop Connection](rdc.png)
4. Choose **Show Options** to view additional connection options.
5. In the **User Name** text box, enter `Administration`, which is the default user name for all Windows instances in Lightsail.
![RDC Administrator](<rdc admin.png>)
6. Choose **Connect**
7. In the prompt that appears, enter or paste the default administrator password that you copied from the Lightsail console earlier in this procedure, and then choose **OK**. The password will be given to you by your Manager.  
![RDC Password](<rdc password.png>)
8. In the prompt that appears, choose Yes to connect to the Windows instance despite certificate errors.  
![RDC Error](<rdc error.png>)
After you’re connected to the instance, you should see a screen similar to the following example:
![VM Desktop](<VM Desktop.png>)