# Malware Model: Anti-Debugging and Self-Deletion

This repository demonstrates a simple malware model that detects the presence of a debugger and deletes itself if one is found. The model uses the PEB structure to detect debuggers and implements a self-deletion technique by manipulating file attributes.

## Features

- **Anti-Debugging**: Detects if the malware is being executed under a debugger by inspecting the PEB (Process Environment Block) structure.
- **Self-Deletion**: If a debugger is detected, the malware deletes itself using a file handle manipulation technique.

## Steps

1. **Create a handle to the current file**: Open the file that corresponds to the running malware.
2. **Get the name of the current file**: Retrieve the name of the executable file currently being run.
3. **Rename the current file**: Temporarily rename the file to avoid conflicts during deletion.
4. **Set the file's attributes for deletion**: Use the `FileDispositionInfo` structure to mark the file for deletion.
5. **Close the handle**: Closing the file handle will trigger the deletion of the file.

## Technical Implementation

### 1. Detecting the Debugger
The malware inspects the PEB structure to determine if a debugger is present. The PEB's `BeingDebugged` flag is checked to confirm whether the process is being debugged.

### 2. Self-Deletion
The malware follows these steps to delete itself:

- Create a handle to the current executable file.
- Retrieve the file's name and temporarily rename it.
- Set the `FileDispositionInfo` struct's `Delete` flag to true.
- Close the file handle, which causes the file to be deleted by the OS.

## If you want To try it just clone the project and compile it with VS Studio 
### Notice : you should disable just-in-time windows defender if you want to run it  
### Usage

#### Run the exe file  with the  process ID thet you want to inject the payload on it (PID) and add if you want The thread Id :

    ```bash
    Selfasini.exe <PID> <TID>
    ```



#### license
all license are preserved  

