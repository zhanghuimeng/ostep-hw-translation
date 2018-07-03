# OSTEP第4章作业模拟程序

本说明翻译自OSTEP第4章作业说明，并将原作者的代码修正为py3版本。原链接为<http://pages.cs.wisc.edu/~remzi/OSTEP/Homework/HW-CPU-Intro.tgz>。

---

此程序名为`process-run.py`，作用是帮助你理解进程在CPU上运行时状态的变化情况。就像本章中描述的那样，进程可能的状态包括以下几种：

* RUNNING（运行态）：进程正在使用CPU
* READY（就绪态）：进程现在已经准备好使用CPU了，但其他进程已经占用了CPU（啊哦！）
* WAITING（等待态）：进程正在等待I/O请求完成（比如向磁盘发送的请求）
* DONE（结束态）：进程已经结束执行

在本次作业中，我们将了解进程的运行过程中进程的状态如何变化，并对进程状态的原理产生更深刻的理解。

执行以下命令以执行程序并查看选项：

```
prompt> ./process-run.py -h
```

If this doesn't work, type "python" before the command, like this:
如果上述命令不起作用，在命令前键入`python`，如下：

```
prompt> python process-run.py -h
```

你应该看到如下输出：
```
Usage: process-run.py [options]

Options:
  -h, --help            show this help message and exit
  -s SEED, --seed=SEED  the random seed
  -l PROCESS_LIST, --processlist=PROCESS_LIST
                        a comma-separated list of processes to run, in the
                        form X1:Y1,X2:Y2,... where X is the number of
                        instructions that process should run, and Y the
                        chances (from 0 to 100) that an instruction will use
                        the CPU or issue an IO
  -L IO_LENGTH, --iolength=IO_LENGTH
                        how long an IO takes
  -S PROCESS_SWITCH_BEHAVIOR, --switch=PROCESS_SWITCH_BEHAVIOR
                        when to switch between processes: SWITCH_ON_IO,
                        SWITCH_ON_END
  -I IO_DONE_BEHAVIOR, --iodone=IO_DONE_BEHAVIOR
                        type of behavior when IO ends: IO_RUN_LATER,
                        IO_RUN_IMMEDIATE
  -c                    compute answers for me
  -p, --printstats      print statistics at end; only useful with -c flag
                        (otherwise stats are not printed)
```

最重要的选项是`PROCESS_LIST`（通过`-l`或`--processlist`标志给定），它明确给定了每个进程的行为。进程由指令组成，每个指令只会进行以下两件事之一：

* 使用CPU
* 发出I/O请求（并等待请求完成）

当进程只使用CPU（完全不进行I/O）时，它应该只在RUNNING和READY状态之间切换。在下面的例子中，只有一个进程在运行，这个进程只使用CPU（不进行I/O）。

```
prompt> ./process-run.py -l 5:100
Produce a trace of what would happen when you run these processes:
Process 0
  cpu
  cpu
  cpu
  cpu
  cpu

Important behaviors:
  System will switch when the current process is FINISHED or ISSUES AN IO
  After IOs, the process issuing the IO will run LATER (when it is its turn)

prompt>
```

此处，参数`5:100`表示这个进程应该包含5条指令，且每条指令是CPU指令的概率为100%。

使用标志`-c`可以帮助你计算出答案（进程的具体切换过程）：

```
prompt> ./process-run.py -l 5:100 -c
Time     PID: 0        CPU        IOs
  1     RUN:cpu          1
  2     RUN:cpu          1
  3     RUN:cpu          1
  4     RUN:cpu          1
  5     RUN:cpu          1
```

这个结果没什么意思：进程进入了运行态，然后结束了，一直在使用CPU，在整个运行过程中CPU始终在执行程序，没有进行任何I/O。

下面我们换一个复杂一点的例子，同时运行两个进程：

```
prompt> ./process-run.py -l 5:100,5:100
Produce a trace of what would happen when you run these processes:
Process 0
  cpu
  cpu
  cpu
  cpu
  cpu

Process 1
  cpu
  cpu
  cpu
  cpu
  cpu

Important behaviors:
  Scheduler will switch when the current process is FINISHED or ISSUES AN IO
  After IOs, the process issuing the IO will run LATER (when it is its turn)
```

在这种情况下，我们运行了两个进程，它们都只使用了CPU。让我们来看看OS执行这两个进程时发生了什么。

```
prompt> ./process-run.py -l 5:100,5:100 -c
Time     PID: 0     PID: 1        CPU        IOs
  1     RUN:cpu      READY          1
  2     RUN:cpu      READY          1
  3     RUN:cpu      READY          1
  4     RUN:cpu      READY          1
  5     RUN:cpu      READY          1
  6        DONE    RUN:cpu          1
  7        DONE    RUN:cpu          1
  8        DONE    RUN:cpu          1
  9        DONE    RUN:cpu          1
 10        DONE    RUN:cpu          1
```

从上述执行结果可以看出，进程0（PID=0）先运行，此时进程1处于就绪态，等待进程0执行完毕。进程0结束后，它进入结束态，进程1开始运行。进程1也结束后，本次模拟过程结束。

在回答问题之前，让我们再看一个例子。在这个例子中，进程只进行I/O请求。我们用标志`-L`指定I/O请求所需的时间片数量，此处为5。

```
prompt> ./process-run.py -l 3:0 -L 5
Produce a trace of what would happen when you run these processes:
Process 0
  io-start
  io-start
  io-start

Important behaviors:
  System will switch when the current process is FINISHED or ISSUES AN IO
  After IOs, the process issuing the IO will run LATER (when it is its turn)
```

你认为实际运行过程会是什么样子的？事实上是这样的：

```
prompt> ./process-run.py -l 3:0 -L 5 -c
Time     PID: 0        CPU        IOs
  1      RUN:io          1
  2     WAITING                     1
  3     WAITING                     1
  4     WAITING                     1
  5     WAITING                     1
  6*     RUN:io          1
  7     WAITING                     1
  8     WAITING                     1
  9     WAITING                     1
 10     WAITING                     1
 11*     RUN:io          1
 12     WAITING                     1
 13     WAITING                     1
 14     WAITING                     1
 15     WAITING                     1
 16*       DONE
```

你会发现，这个程序只进行了3次I/O请求。每次发出一个I/O请求之后，进程就进入等待（WAITING）状态；当设备处理I/O请求时，CPU空闲。

Let's print some stats (run the same command as above, but with the -p flag)
to see some overall behaviors:

下面让我们打印一些统计数据（执行命令`./process-run.py -l 3:0 -L 5 -p`）以了解整体表现：

```
Stats: Total Time 16
Stats: CPU Busy 3 (18.75%)
Stats: IO Busy  12 (75.00%)
```

你会发现，上面的模拟过程花了16个时钟周期来运行，但CPU被占用的时间只有不到20%。而I/O设备的利用率却很高。整体来说，我们希望所有设备的利用率都比较高，因为这可以更好的利用资源。

还有一些其他的重要选项：

* `-s SEED, --seed=SEED`：给定随机种子；可以随机创建很多不同的任务
* `-L IO_LENGTH, --iolength=IO_LENGTH`：指定I/O请求所需的完成时间（默认为5个时间片）
* `-S PROCESS_SWITCH_BEHAVIOR, --switch=PROCESS_SWITCH_BEHAVIOR`：何时在进程之间进行切换，可选值为`SWITCH_ON_IO`和`SWITCH_ON_END`
  * `SWITCH_ON_IO`：在进程发出I/O请求时进行进程切换（默认值）
  * `SWITCH_ON_END`：只在当前进程运行结束时才进行切换，发出I/O请求时不切换。
* `-I IO_DONE_BEHAVIOR, --iodone=IO_DONE_BEHAVIOR`：进程的I/O请求完成时的行为，可选值为`IO_RUN_LATER`和`IO_RUN_IMMEDIATE`
  * `IO_RUN_LATER`：立刻抢占CPU
  * `IO_RUN_IMMEDIATE`：不立刻抢占CPU，进程何时开始执行取决于现在运行中进程的运行状态和进程切换策略（默认值）

现在去回答本章的作业题吧，这样就能学到更多东西了。
