spark-tcptest
=============

Spark Core TCP connection tester

After much fun messing around with TCPClient I realized there are just too many community posts with bad examples that just aren't complete, work around library bugs that have already been fixed, or were otherwise incorrect.

So after many hours of working on my own example, I finally have one that is complete, robust, and maybe even good enough for usage in the real world.  It can deal with connection timeouts, slow/unresponsive servers, high latency connections, sudden disconnects, etc.

Now, it doesn't do anything particularly useful on its own, but it should provide a very nice starting point for your own projects -- letting you get headaches over your own application level problems, not some lower level TCP communications crap!

So how do you use this thing?

1. Set up a listening server somewhere (a linux box with netcat is quite handy).
2. Be sure to set the SERVER_IP and SERVER_PORT values at the top!!!
3. Tweak the timeout/delay values if desired.
4. Flash it to your core and let the fun begin.
5. Connect via USB serial and you get a little bit of status info.

Using netcat, for example, you can try various ways of "responding" to the client after you see the hello it sends upon connection.  Try doing nothing, try typing some text and hitting enter, try typing several lines of text and then waiting around, just send an EOF (hit CTRL+D), or some type in one or more lines of text and then an EOF.

Disclaimer:
AS-IS
NO WARRANTY
etc.
