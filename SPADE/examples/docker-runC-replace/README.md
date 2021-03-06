## Docker-runC OverWrite Scenario - CVE-2019-5736 ##

In this scenario. Host file /usr/bin/docker-runc is overritten using program/malicios_image_poc/overrite_runc.c. The code overrites the said file using symlink file descriptor `/proc/<id self>/fd/3`. And to verify the process, it creates a test file inside the same program named as rc5.txt. Both of these files are connected to a process with container namespaces. Target is to find lineage from this container to the actual file which /fd/3 is representing. Which in this case is the /usr/bin/docker-runc file. There is a path from that container-process-vertex to the artifact `/usr/bin/docker-runc` which can be searched while dotting the graph file to svg and then searching '/usr/bin/docker-runc'. There are 54 results and this can be found at 17th search item. 

The flow can be re iterated through SPADE's audit reporter. Before that. disp_qos property should be set to lossless under /etc/audit/auditd.conf. And before running the run.sh. SPADE should be started and reporter Audit should be added. 

To that end, there is a simple program provided, the SPADE log for the SPADE run, the Audit log for the program (in skype channel), and the DOT graph for the program. Files with the extension `.gz` can be uncompressed using the command `gunzip <name of the file>`.

## Program ##

The `program` directory contains the POC which can be found [here](https://github.com/twistlock/RunC-CVE-2019-5736) which in this case is the second method. Two scripts are provided which should be run in the following order:

* 1-Build: `./setup.sh`
* 2-Run: `./run.sh`

Note: The scripts may require executable access using `chmod +x setup.sh` and `chmod +x run.sh`.

## SPADE Log ##

The file `SPADE_07.29.2021-22.17.12` is a SPADE log file which contains the result of detecting crossnaespaces events while spade run. The intial list of crossname space events can be printed using:

`grep 'CrossNamespaces event' SPADE_07.29.2021-22.17.12.log | grep "789939"`

This will print all crossnamespace events to inode 789939, this can further be further narrowed down to namespaces of interests. i.e of container and host etc. (Note: namespaces with -1 can be ignored if found)
## Audit Log ##

shared in skype channel using commit hash. 
## query ##
query directory contains two queries. One with level 1 and one with level 3. The purpose of both queries is expressed in graph section

##Graph ##

The file `runc.dot.gz` under `graph` directory is the DOT graph for the program above with level 3 to show connections of an inode=789939 which is written by direct and symlink paths. Another graph alongwith svg is uploaded with level, which is disconnected graph of the same inode giving inforation of the file being accessed in different ways.
