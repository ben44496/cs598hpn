# cs598hpn

## Instructions
1. Startup docker container, which will automatically set up ns3
2. Navigate to `root@7eee0585976a:/usr/ns-allinone-3.40/ns-3.40/`
3. Run the following lines:
   1. `$ ./ns3 configure --enable-examples --enable-tests`
   2. `$ ./ns3 build`
  If these come back ok, then ns3 is working.
4. Now go to the `cs598-echo-client` branch and copy the folder in there to `/usr/ns-allinone-3.40/ns-3.40/contrib`
5. Now run `$ ./ns3 build` again.
6. Run `$ ./ns3 run contrib/cs598-echo-client/examples/example.cc > output.txt 2>&1`
   1. This should output the results of running the simualtion to `output.txt`
   2. It should look like the below example output.


## Example Output

```txt
Consolidate compiler generated dependencies of target example
[  0%] Building CXX object contrib/cs598-echo-client/examples/CMakeFiles/example.dir/example.cc.o
[  4%] Linking CXX executable ../../../../build/contrib/cs598-echo-client/examples/ns3.40-example-default
T+2s: Packet loss fast: 0, slow: 0
T+2s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2s: Sent fast path.
T+2.01s: Packet loss fast: 0, slow: 0
T+2.01s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.01s: Sent fast path.
T+2.02s: Packet loss fast: 0, slow: 0
T+2.02s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.02s: Sent fast path.
T+2.03s: Packet loss fast: 0, slow: 0
T+2.03s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.03s: Sent fast path.
T+2.04s: Packet loss fast: 0, slow: 0
T+2.04s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.04s: Sent fast path.
At time +2.04001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.04001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.05s: Packet loss fast: 0, slow: 0
T+2.05s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.05s: Sent fast path.
T+2.06s: Packet loss fast: 0, slow: 0
T+2.06s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.06s: Sent fast path.
At time +2.06001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.06001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.07s: Packet loss fast: 0, slow: 0
T+2.07s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.07s: Sent fast path.
At time +2.07001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.07001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.08s: Packet loss fast: 0, slow: 0
T+2.08s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.08s: Sent fast path.
At time +2.08001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.08001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.09s: Packet loss fast: 0, slow: 0
T+2.09s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.09s: Sent fast path.
At time +2.09001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.09001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.1s: Packet loss fast: 0, slow: 0
T+2.1s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.1s: Sent fast path.
At time +2.10001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.10001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.11s: Packet loss fast: 0, slow: 0
T+2.11s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.11s: Sent fast path.
T+2.11001s: Received from fast
3
T+2.12s: Packet loss fast: 0, slow: 0
T+2.12s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.12s: Sent fast path.
T+2.12001s: Received from fast
4
T+2.13s: Packet loss fast: 0, slow: 0
T+2.13s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.13s: Sent fast path.
At time +2.13001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.13001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.14s: Packet loss fast: 0, slow: 0
T+2.14s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.14s: Sent fast path.
At time +2.14001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.14001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.14001s: Received from fast
6
T+2.15s: Packet loss fast: 0, slow: 0
T+2.15s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.15s: Sent fast path.
At time +2.15001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.15001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.16s: Packet loss fast: 0, slow: 0
T+2.16s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.16s: Sent fast path.
At time +2.16001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.16001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.17s: Packet loss fast: 0, slow: 0
T+2.17s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.17s: Sent fast path.
At time +2.17001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.17001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.17001s: Received from fast
9
T+2.18s: Packet loss fast: 0, slow: 0
T+2.18s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.18s: Sent fast path.
At time +2.18001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.18001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.19s: Packet loss fast: 0, slow: 0
T+2.19s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.19s: Sent fast path.
T+2.19001s: Received from fast
11
T+2.2s: Packet loss fast: 0, slow: 0
T+2.2s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.2s: Sent fast path.
T+2.21s: Packet loss fast: 0, slow: 0
T+2.21s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.21s: Sent fast path.
At time +2.21001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.21001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.21001s: Received from fast
13
T+2.22s: Packet loss fast: 0, slow: 0
T+2.22s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.22s: Sent fast path.
At time +2.22001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.22001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.23s: Packet loss fast: 0, slow: 0
T+2.23s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.23s: Sent fast path.
T+2.24s: Packet loss fast: 0, slow: 0
T+2.24s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.24s: Sent fast path.
At time +2.24001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.24001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.25s: Packet loss fast: 0, slow: 0
T+2.25s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.25s: Sent fast path.
At time +2.25001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.25001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.26s: Packet loss fast: 0, slow: 0
T+2.26s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.26s: Sent fast path.
At time +2.26001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.26001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.26001s: Received from fast
18
T+2.27s: Packet loss fast: 0, slow: 0
T+2.27s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.27s: Sent fast path.
At time +2.27001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.27001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.28s: Packet loss fast: 0, slow: 0
T+2.28s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.28s: Sent fast path.
At time +2.28001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.28001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.28001s: Received from fast
20
T+2.29s: Packet loss fast: 0, slow: 0
T+2.29s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.29s: Sent fast path.
At time +2.29001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.29001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.29001s: Received from fast
21
T+2.3s: Packet loss fast: 0, slow: 0
T+2.3s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.3s: Sent fast path.
At time +2.30001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.30001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.31s: Packet loss fast: 0, slow: 0
T+2.31s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.31s: Sent fast path.
At time +2.31001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.31001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.31001s: Received from fast
23
T+2.32s: Packet loss fast: 0, slow: 0
T+2.32s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.32s: Sent fast path.
At time +2.32001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.32001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.32001s: Received from fast
24
T+2.33s: Packet loss fast: 0, slow: 0
T+2.33s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.33s: Sent fast path.
At time +2.33001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.33001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.33001s: Received from fast
25
T+2.34s: Packet loss fast: 0, slow: 0
T+2.34s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.34s: Sent fast path.
At time +2.34001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.34001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.35s: Packet loss fast: 0, slow: 0
T+2.35s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.35s: Sent fast path.
At time +2.35001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.35001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.36s: Packet loss fast: 0, slow: 0
T+2.36s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.36s: Sent fast path.
T+2.36001s: Received from fast
28
T+2.37s: Packet loss fast: 0, slow: 0
T+2.37s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.37s: Sent fast path.
T+2.38s: Packet loss fast: 0, slow: 0
T+2.38s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.38s: Sent fast path.
At time +2.38001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.38001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.38001s: Received from fast
30
T+2.39s: Packet loss fast: 0, slow: 0
T+2.39s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.39s: Sent fast path.
At time +2.39001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.39001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.39001s: Received from fast
31
T+2.4s: Packet loss fast: 0, slow: 0
T+2.4s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.4s: Sent fast path.
T+2.41s: Packet loss fast: 0, slow: 0
T+2.41s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.41s: Sent fast path.
At time +2.41001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.41001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.42s: Packet loss fast: 0, slow: 0
T+2.42s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.42s: Sent fast path.
At time +2.42001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.42001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.42001s: Received from fast
34
T+2.43s: Packet loss fast: 0, slow: 0
T+2.43s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.43s: Sent fast path.
T+2.43001s: Received from fast
35
T+2.44s: Packet loss fast: 0, slow: 0
T+2.44s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.44s: Sent fast path.
At time +2.44001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.44001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.45s: Packet loss fast: 0, slow: 0
T+2.45s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.45s: Sent fast path.
At time +2.45001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.45001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.45001s: Received from fast
37
T+2.46s: Packet loss fast: 0, slow: 0
T+2.46s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.46s: Sent fast path.
T+2.47s: Packet loss fast: 0, slow: 0
T+2.47s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.47s: Sent fast path.
At time +2.47001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.47001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.48s: Packet loss fast: 0, slow: 0
T+2.48s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.48s: Sent fast path.
At time +2.48001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.48001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.49s: Packet loss fast: 0, slow: 0
T+2.49s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.49s: Sent fast path.
At time +2.49001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.49001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.49001s: Received from fast
41
T+2.5s: Packet loss fast: 0, slow: 0
T+2.5s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.5s: Sent fast path.
At time +2.50001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.50001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.51s: Packet loss fast: 0, slow: 0
T+2.51s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.51s: Sent fast path.
At time +2.51001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.51001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.51001s: Received from fast
43
T+2.52s: Packet loss fast: 0, slow: 0
T+2.52s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.52s: Sent fast path.
At time +2.52001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.52001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.53s: Packet loss fast: 0, slow: 0
T+2.53s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.53s: Sent fast path.
T+2.53001s: Received from fast
45
T+2.54s: Packet loss fast: 0, slow: 0
T+2.54s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.54s: Sent fast path.
T+2.54001s: Received from fast
46
T+2.55s: Packet loss fast: 0, slow: 0
T+2.55s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.55s: Sent fast path.
At time +2.55001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.55001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.55001s: Received from fast
47
T+2.56s: Packet loss fast: 0, slow: 0
T+2.56s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.56s: Sent fast path.
At time +2.56001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.56001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.56001s: Received from fast
48
T+2.57s: Packet loss fast: 0, slow: 0
T+2.57s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.57s: Sent fast path.
At time +2.57001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.57001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.58s: Packet loss fast: 0, slow: 0
T+2.58s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.58s: Sent fast path.
T+2.59s: Packet loss fast: 0, slow: 0
T+2.59s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.59s: Sent fast path.
T+2.59001s: Received from fast
51
T+2.6s: Packet loss fast: 0, slow: 0
T+2.6s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.6s: Sent fast path.
At time +2.60001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.60001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.61s: Packet loss fast: 0, slow: 0
T+2.61s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.61s: Sent fast path.
At time +2.61001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.61001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.61001s: Received from fast
53
T+2.62s: Packet loss fast: 0, slow: 0
T+2.62s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.62s: Sent fast path.
T+2.63s: Packet loss fast: 0, slow: 0
T+2.63s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.63s: Sent fast path.
At time +2.63001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.63001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.64s: Packet loss fast: 0, slow: 0
T+2.64s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.64s: Sent fast path.
T+2.65s: Packet loss fast: 0, slow: 0
T+2.65s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.65s: Sent fast path.
At time +2.65001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.65001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.65001s: Received from fast
57
T+2.66s: Packet loss fast: 0, slow: 0
T+2.66s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.66s: Sent fast path.
T+2.67s: Packet loss fast: 0, slow: 0
T+2.67s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.67s: Sent fast path.
At time +2.67001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.67001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.67001s: Received from fast
59
T+2.68s: Packet loss fast: 0, slow: 0
T+2.68s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.68s: Sent fast path.
At time +2.68001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.68001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.69s: Packet loss fast: 0, slow: 0
T+2.69s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.69s: Sent fast path.
At time +2.69001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.69001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.69001s: Received from fast
61
T+2.7s: Packet loss fast: 0, slow: 0
T+2.7s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.7s: Sent fast path.
T+2.71s: Packet loss fast: 0, slow: 0
T+2.71s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.71s: Sent fast path.
T+2.72s: Packet loss fast: 0, slow: 0
T+2.72s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.72s: Sent fast path.
T+2.72001s: Received from fast
64
T+2.73s: Packet loss fast: 0, slow: 0
T+2.73s: pA: 0, pB: 0, Tfast: 0.04, Tslow: 0.06
T+2.73s: Sent fast path.
At time +2.73001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.73001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.73001s: Received from fast
65
T+2.74s: Packet loss fast: 1, slow: 0
T+2.74s: pA: 0.015625, pB: 0, Tfast: 0.0419355, Tslow: 0.06
T+2.74s: Sent fast path.
T+2.75s: Packet loss fast: 1, slow: 0
T+2.75s: pA: 0.015625, pB: 0, Tfast: 0.0419355, Tslow: 0.06
T+2.75s: Sent fast path.
At time +2.75001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.75001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.76s: Packet loss fast: 1, slow: 0
T+2.76s: pA: 0.015625, pB: 0, Tfast: 0.0419355, Tslow: 0.06
T+2.76s: Sent fast path.
T+2.77s: Packet loss fast: 1, slow: 0
T+2.77s: pA: 0.015625, pB: 0, Tfast: 0.0419355, Tslow: 0.06
T+2.77s: Sent fast path.
At time +2.77001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.77001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.77001s: Received from fast
69
T+2.78s: Packet loss fast: 3, slow: 0
T+2.78s: pA: 0.046875, pB: 0, Tfast: 0.0462069, Tslow: 0.06
T+2.78s: Sent fast path.
At time +2.78001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.78001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.79s: Packet loss fast: 3, slow: 0
T+2.79s: pA: 0.046875, pB: 0, Tfast: 0.0462069, Tslow: 0.06
T+2.79s: Sent fast path.
At time +2.79001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.79001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.8s: Packet loss fast: 3, slow: 0
T+2.8s: pA: 0.046875, pB: 0, Tfast: 0.0462069, Tslow: 0.06
T+2.8s: Sent fast path.
T+2.81s: Packet loss fast: 3, slow: 0
T+2.81s: pA: 0.046875, pB: 0, Tfast: 0.0462069, Tslow: 0.06
T+2.81s: Sent fast path.
T+2.82s: Packet loss fast: 3, slow: 0
T+2.82s: pA: 0.046875, pB: 0, Tfast: 0.0462069, Tslow: 0.06
T+2.82s: Sent fast path.
At time +2.82001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.82001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.82001s: Received from fast
74
T+2.83s: Packet loss fast: 6, slow: 0
T+2.83s: pA: 0.09375, pB: 0, Tfast: 0.0538462, Tslow: 0.06
T+2.83s: Sent fast path.
At time +2.83001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.83001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.83001s: Received from fast
75
T+2.84s: Packet loss fast: 6, slow: 0
T+2.84s: pA: 0.09375, pB: 0, Tfast: 0.0538462, Tslow: 0.06
T+2.84s: Sent fast path.
At time +2.84001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.84001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.85s: Packet loss fast: 6, slow: 0
T+2.85s: pA: 0.09375, pB: 0, Tfast: 0.0538462, Tslow: 0.06
T+2.85s: Sent fast path.
At time +2.85001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.85001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.86s: Packet loss fast: 6, slow: 0
T+2.86s: pA: 0.09375, pB: 0, Tfast: 0.0538462, Tslow: 0.06
T+2.86s: Sent fast path.
T+2.86001s: Received from fast
78
T+2.87s: Packet loss fast: 8, slow: 0
T+2.87s: pA: 0.125, pB: 0, Tfast: 0.06, Tslow: 0.06
T+2.87s: Sent fast path.
At time +2.87001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.87001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.87001s: Received from fast
79
T+2.88s: Packet loss fast: 9, slow: 0
T+2.88s: pA: 0.140625, pB: 0, Tfast: 0.0634783, Tslow: 0.06
T+2.88s: Sent slow path.
At time +2.88001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.88001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.89s: Packet loss fast: 9, slow: 0
T+2.89s: pA: 0.140625, pB: 0, Tfast: 0.0634783, Tslow: 0.06
T+2.89s: Sent slow path.
At time +2.89001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.89001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.89001s: Received from slow
81
T+2.9s: Packet loss fast: 9, slow: 17
T+2.9s: pA: 0.140625, pB: 0.265625, Tfast: 0.0634783, Tslow: 0.162
T+2.9s: Sent fast path.
At time +2.90001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.90001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.91s: Packet loss fast: 9, slow: 17
T+2.91s: pA: 0.140625, pB: 0.265625, Tfast: 0.0634783, Tslow: 0.162
T+2.91s: Sent fast path.
At time +2.91001s server received 4 bytes from 10.1.1.1 port 49153
At time +2.91001s server sent 4 bytes to 10.1.1.1 port 49153
T+2.91001s: Received from slow
83
T+2.92s: Packet loss fast: 9, slow: 19
T+2.92s: pA: 0.140625, pB: 0.296875, Tfast: 0.0634783, Tslow: 0.191538
T+2.92s: Sent fast path.
T+2.92001s: Received from slow
84
T+2.93s: Packet loss fast: 9, slow: 20
T+2.93s: pA: 0.140625, pB: 0.3125, Tfast: 0.0634783, Tslow: 0.21
T+2.93s: Sent fast path.
T+2.93001s: Received from slow
85
T+2.94s: Packet loss fast: 9, slow: 21
T+2.94s: pA: 0.140625, pB: 0.328125, Tfast: 0.0634783, Tslow: 0.231818
T+2.94s: Sent fast path.
At time +2.94s server received 4 bytes from 10.1.2.1 port 49154
At time +2.94s server sent 4 bytes to 10.1.2.1 port 49154
T+2.95s: Packet loss fast: 9, slow: 21
T+2.95s: pA: 0.140625, pB: 0.328125, Tfast: 0.0634783, Tslow: 0.231818
T+2.95s: Sent fast path.
At time +2.95s server received 4 bytes from 10.1.2.1 port 49154
At time +2.95s server sent 4 bytes to 10.1.2.1 port 49154
T+2.95001s: Received from slow
87
T+2.96s: Packet loss fast: 9, slow: 23
T+2.96s: pA: 0.140625, pB: 0.359375, Tfast: 0.0634783, Tslow: 0.29
T+2.96s: Sent fast path.
At time +2.96s server received 4 bytes from 10.1.2.1 port 49154
At time +2.96s server sent 4 bytes to 10.1.2.1 port 49154
T+2.97s: Packet loss fast: 9, slow: 23
T+2.97s: pA: 0.140625, pB: 0.359375, Tfast: 0.0634783, Tslow: 0.29
T+2.97s: Sent fast path.
At time +2.97s server received 4 bytes from 10.1.2.1 port 49154
At time +2.97s server sent 4 bytes to 10.1.2.1 port 49154
T+2.98s: Packet loss fast: 9, slow: 23
T+2.98s: pA: 0.140625, pB: 0.359375, Tfast: 0.0634783, Tslow: 0.29
T+2.98s: Sent fast path.
At time +2.98s server received 4 bytes from 10.1.2.1 port 49154
At time +2.98s server sent 4 bytes to 10.1.2.1 port 49154
T+2.99s: Packet loss fast: 9, slow: 23
T+2.99s: pA: 0.140625, pB: 0.359375, Tfast: 0.0634783, Tslow: 0.29
T+2.99s: Sent fast path.
At time +2.99s server received 4 bytes from 10.1.2.1 port 49154
At time +2.99s server sent 4 bytes to 10.1.2.1 port 49154
At time +3s server received 4 bytes from 10.1.2.1 port 49154
At time +3s server sent 4 bytes to 10.1.2.1 port 49154
T+3s: Received from fast
0
At time +3.01s server received 4 bytes from 10.1.2.1 port 49154
At time +3.01s server sent 4 bytes to 10.1.2.1 port 49154
T+3.01s: Received from fast
1
At time +3.02s server received 4 bytes from 10.1.2.1 port 49154
At time +3.02s server sent 4 bytes to 10.1.2.1 port 49154
T+3.02s: Received from fast
88
At time +3.03s server received 4 bytes from 10.1.2.1 port 49154
At time +3.03s server sent 4 bytes to 10.1.2.1 port 49154
T+3.03s: Received from fast
89
At time +3.04s server received 4 bytes from 10.1.2.1 port 49154
At time +3.04s server sent 4 bytes to 10.1.2.1 port 49154
T+3.04s: Received from fast
90
At time +3.05s server received 4 bytes from 10.1.2.1 port 49154
At time +3.05s server sent 4 bytes to 10.1.2.1 port 49154
T+3.05s: Received from fast
91
T+3.06s: Received from fast
92
T+3.07s: Received from fast
93
T+3.08s: Received from fast
94
T+3.09s: Received from fast
95
T+3.1s: Received from fast
96
T+3.11s: Received from fast
97
Total packets sent: 100
Total packets dropped: 47
```