'Map network drive
msgbox "Brads Script -> This will setup your computer so you can access the [whatever] Server"


'Find out next available drive letter for mapping latter on
set objFS=CreateObject ("Scripting.FileSystemObject")
set colDrives=objFS.Drives
letter=Asc("c")
while objFS.DriveExists(Chr(letter)+":")
	letter=letter+1
wend
letter=UCASE(Chr(letter))+":"

'see if they are connected to the vpn
if ping("SOME.ARBRITRARY.IP.HERE")=True then
	msgbox("It appears as though you are connected to the VPN ... Attempting to map network drive")
	Set oNet = CreateObject("WScript.Network")
	onet.MapNetworkDrive letter, "\\Some.Arbritrary.IP.HERE\SomeShare"
	Set objShell = CreateObject("Shell.Application")
	objShell.NameSpace(letter).Self.Name = "Some Server"
	msgbox("Your computer has been setup to use VPN. Just go to 'My Computer' and use the "+letter+" Drive (Some Server)")
	
else
	msgbox("It appears as though you are NOT connected to the UK VPN ... Please connect to the VPN by double clicking the shortcut on your desktop . If you need help let brad know")
end if

Function Ping(strHost)

    dim objPing, objRetStatus

    set objPing = GetObject("winmgmts:{impersonationLevel=impersonate}").ExecQuery _
      ("select * from Win32_PingStatus where address = '" & strHost & "'")

    for each objRetStatus in objPing
        if IsNull(objRetStatus.StatusCode) or objRetStatus.StatusCode<>0 then
    Ping = False
            'WScript.Echo "Status code is " & objRetStatus.StatusCode
        else
            Ping = True
            'Wscript.Echo "Bytes = " & vbTab & objRetStatus.BufferSize
            'Wscript.Echo "Time (ms) = " & vbTab & objRetStatus.ResponseTime
            'Wscript.Echo "TTL (s) = " & vbTab & objRetStatus.ResponseTimeToLive
        end if
    next
End Function 




Wscript.Quit


