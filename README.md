# Interactive virtual file system

## Description

A virtual file system (VFS) is an abstraction layer on top of a concrete file system that provides the ability manage information about files and folders present in the hard disk. The purpose of a VFS is to allow client applications to access different types of concrete file systems in a uniform way. A VFS can, for example, be used to access local and network storage devices transparently without the client application noticing the difference.
(Refer: http://en.wikipedia.org/wiki/Virtual_file_system) All operations, file system operations are UNIX type.

##Glossary of Terms

- File System – A system that provides a unified mechanism for managing data that is organized in the form of files
- File Blocks – Fundamental storage unit into which files are actually stored. A single file may span across multiple file blocks
- File Descriptors – A data structure that contains meta-data information about the file (name, type, location, etc.)

##Overview

File System is basically a large file which stores the data contained in all the existing files. Each file/folder in a file system has a corresponding File descriptor which stores all the information of the file /folder e.g. Size, name, path etc. File system is divided into data blocks of fixed size which store the actual file contents. The files when saved in the file system can be scattered over multiple blocks depending upon the size of the file.

Example:
Suppose there is a file system of 10 Kb divided into 10 data blocks (0-9) of 1Kb each. Suppose there are three files a.txt, b.txt, and c.txt each of size 1.25 Kb.
-- a.txt resides in blocks 0,1
--b.txt resides in blocks 2,5
--c.txt resides in block 3,4

The file system in this project consists of three parts as shown in the figure.
- Meta Header [Fixed size]: Number of file descriptors present	
- Header [Fixed size]: 
-- File descriptors of each file/folder in the file system. These file descriptors would be needed to populate n-array tree for the directory structure and hash table for faster searching for files.
-- There would be a separate free_block_list which contains the list of all the free blocks in the file system.
- File Blocks:  Each identified with an index number or an offset.

- Meta header (fixed size)
(name of file system, number of used file descriptors)
Header (max of N file descriptors + Free list)
(fd_01, fd_02, … fd_N)
Block 0
Block 1
Block 2
…….
Block n-1
