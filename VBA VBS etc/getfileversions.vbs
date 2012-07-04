'Retrives file versions for files in the hard coded directory. 

Option Explicit
Dim fso, fc, f, fs ,oShell 
Dim strPath, strFile,profile

'On Error Resume Next

Set oShell=CreateObject("Wscript.Shell")
profile=oShell.ExpandEnvironmentStrings("%USERPROFILE%")

strPath = profile+"\desktop\fileversions.txt"
Set fso = CreateObject("Scripting.FileSystemObject")
Set strFile = fso.CreateTextFile(strPath, True)
strFile.WriteLine("FileName,Last Modified,File Version")
Set f = fso.GetFolder("C:\Program Files (x86)\Benchmark V7")          
Set fc = f.Files

For Each fs In fc
	strFile.WriteLine(fs.Name & "," & fs.DateLastModified & "," & fso.GetFileVersion(fs))
Next