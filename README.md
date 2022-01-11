# CLog
Logging lib for C and embedded firmware

| Level | Value | Decription |
| :-: | :-: | :- |
| OFF | 0 | The highest possible rank and is intended to turn off logging. |
| FATAL | 1 | Designates very severe error events that will presumably lead the application to abort. |
| ERROR | 2 | Designates error events that might still allow the application to continue running. |
| WARN | 3 | Designates potentially harmful situations. |
| INFO | 4 | Designates informational messages that highlight the progress of the application at coarse-grained level. |
| DEBUG | 5 | Designates fine-grained informational events that are most useful to debug an application. |
| TRACE | 6 | Designates finer-grained informational events than the DEBUG. |
| ... | ... | |
| ALL | 255 | All levels including custom levels. |
