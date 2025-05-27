# RecyclePathInspector
By using metadata, scan the files in the Windows Recycle Bin and parse the original paths.
![image](https://github.com/user-attachments/assets/9c13c302-b1dd-49f8-9bf4-3df20a5af7b9)


The principle is to obtain the original path of the deleted file by parsing the metadata structure of the files with the prefix "$I" in the Recycle Bin.

This project is set to run by default, which enables the export of the original locations of all deleted files, including the deletion time.

It will generate recycle_report.csv in the current working directory.
![image](https://github.com/user-attachments/assets/179f6d85-f139-4350-a774-45f2c2b62483)
