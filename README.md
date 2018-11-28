## Komodo Dapps

### zmigrate

**Q.** What is zmigrate?
**A.** App to send funds from zc address to zs address directly, sprout to sapling. 

More detailed description:

z_migrate: the purpose of z_migrate is to make converting of all sprout outputs into sapling. the usage would be for the user to specify a sapling address and call z_migrate zsaddr, until it returns that there is nothing left to be done.

its main functionality is quite similar to a z_mergetoaddress ANY_ZADDR -> onetime_taddr followed by a z_sendmany onetime_taddr -> zsaddr

since the z_mergetoaddress will take time, it would just queue up an async operation. When it starts, it should see if there are any onetime_taddr with 10000.0001 funds in it, that is a signal for it to do the sapling tx and it can just do that without async as it is fast enough, especially with a taddr input. Maybe it limits itself to one,  or it does all possible taddr -> sapling as fast as it can. either is fine as it will be called over and over anyway.

It might be that there is nothing to do, but some operations are pending. in that case it would return such a status. as soon as the operation finishes, there would be more work to do.

the amount sent to the taddr, should be 10000.0001

The GUI or user would be expected to generate a sapling address and then call z_migrate saplingaddr, until it returns that it is all done. this loop should pause for 10 seconds or so, if z_migrate is just waiting for opid to complete.

![](./docs/ifMbGoA0_q.png) 

**Q.** Is zmigrate available for Windows / Linux / MacOS users?
**A.** Linux users can built zmigrate dapp from this repo using `./makedapps` or from original komodod repo, it located in [src/cc/dapps](https://github.com/jl777/komodo/tree/dev/src/cc/dapps) . Windows users can build zmigrate using `dapps_win.sln` solution file for MSVC. We recommend to use Microsoft Visual Studio Professional 2015 Version 14.0.25431.01 Update 3 for build.