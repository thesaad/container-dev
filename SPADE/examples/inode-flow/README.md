## Cross-namespaces Scenario ##

In this scenario, a program `writer` (in namespace `X`) writes to a file, and a `reader` (in namespaces `Y`) reads from the same file. This creates a cross-namespaces data flow through a file.

This is to demonstrate that cross-namespaces data flow through inodes can be captured using SPADE's Audit reporter, and the CrossNamespaces filter.

To that end, there is a simple program provided, the SPADE log for the SPADE run, the Audit log for the program, and the DOT graph for the program. Files with the extension `.gz` can be uncompressed using the command `gunzip <name of the file>`.

## Program ##

The `program` directory contains the program which is derived from a Camflow example [here](https://github.com/CamFlow/examples/tree/master/namespaces).

* Build: `make all`
* Run: `make run`

Note: The program is run as `root` so that activity is captured by SPADE. Also, the program outputs the inode of the file through which cross-namespaces data flow occurs to help track it in other log files.

## SPADE Log ##

The file `SPADE_07.14.2021-13.34.57.log` is a SPADE log file which contains the result of detecting cross-namespaces dataflow using the CrossNamespaces filter.

The CrossNamespaces filter events #12, and #13 refer to the cross-namespaces data flow caused by the program above. The inode involved in these events can be found in the logs below for sanity checking.

## Audit Log ##

The file `namespaces.inodes.log` is the Audit log that was captured for the program above.

## DOT Graph ##

The file `namespaces.inodes.dot` is the DOT graph for the program above.
