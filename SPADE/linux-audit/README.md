## Linux Audit Subsystem ##

Linux Audit Subsystem is used by the SPADE's Audit reporter to capture whole-system provenance.

## Configuration ##

The value of `disp_qos` should be `lossless` in the file `/etc/audit/auditd.conf` to avoid loss of events. [Source](https://linux.die.net/man/8/auditd.conf).

The value of `q_depth` should be increased to `9999` in the file `/etc/audisp/audispd.conf` to avoid log of events, too.

Any update to the files above requires the `auditd` service to be restarted, as follows:

```
user@host:~/$ sudo service auditd stop && sudo service auditd start
```

In practice, the command `sudo service auditd restart` wasn't found to be consistently reliable for restarting `auditd` service.

The status of Linux Audit can be viewed by:
```
user@host:~/$ auditctl -s
enabled 1
failure 1
pid 362
rate_limit 0
backlog_limit 8192
lost 0
backlog 0
backlog_wait_time 0
loginuid_immutable 0 unlocked
```

The number of audit events that can be queued in kernel is specified by `backlog_limit` in the output above. It can be increased by using the command:
```
user@host:~/$ auditctl -b 16384
``` 

A good practice is to keep track of `lost` in the output above to ensure that no audit events were lost.

