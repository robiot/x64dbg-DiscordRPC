# x64dbg DiscordRPC
A quite simple plugin to display when your using x64dbg and what binary you are debugging on discord. For example ![image](https://user-images.githubusercontent.com/68228472/111080893-590a9e00-8509-11eb-846e-db4b3678e4f6.png)

## How to use
Using this plugin is pretty straightforward
1. Download the x64dbgRPC zip file from the [releases](https://github.com/robi0t/x64dbg-DiscordRPC/releases) tab and extract it
2. Open the directory where x64dbg is located. It should look like this:

![image](https://user-images.githubusercontent.com/68228472/111081132-79872800-850a-11eb-95ba-b9de3a902da1.png)

3. Open the x32 folder and press "plugins" (if plugins folder doesen't exist just create it)
4. Drag/copy the .dp32 file from the extracted folder to the plugins folder
5. Repeat the same things as in the steps 3&4 but with the x64 folder & .dp64 extension instead

`Now start x64dbg and if you look at discord it should display that you are using x64dbg`

## How to compile
If you would like to compile yourself then this is how
1. Open the .sln file with **Visual Studio 2019** 
2. Change debug to release and change `to x86 for x32dbg` and `to x64 for x64dbg` (make sure the project conifiguration type is set to **dynamic library (.dll)**)
3. Compile!!!
4. Drag the compiled dll into the plugins folder inside x64dbg and rename the file extension from **.dll** to `.dp32 for x32dbg` or `.dp64 for x64dbg`
5. Start x64dbg and check discord if it worked :)
  
## More Information  
This plugin was tested on a Windows10 x64 bit machine

**Why?** I didn't find any discord rpc for x64dbg so i decided to make one :)

**If you experience any error or have a suggestion please let me know**
\
\
\
[More x64dbg plugins](https://github.com/x64dbg/x64dbg/wiki/Plugins)
 
*-robi0t*
