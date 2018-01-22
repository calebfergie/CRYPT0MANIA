# CRYPT0MANIA
## This is the repository for everything related to the CRYPT0MANIA project
Sup cryptofam! This project was demo'd at the [2017 ITP Winter Show](https://itp.nyu.edu/shows/winter2017/crypt0mania/) and details on its creation can be found [here](http://www.blog.calebfergie.com/2017/12/29/api-to-led-8/), with more detail on the code [here](http://www.blog.calebfergie.com/2017/12/21/api-to-led-6/).

The crystal now lives on my windowsill, with a livestream _TBD. ETA February 2018._

## Notes about this repository
Arguably the most important file in this repo is the **[WeMos code](https://github.com/calebfergie/CRYPT0MANIA/blob/master/weMos_code.ino)**. The WeMos device is the microcontroller (i.e. knockoff Arduino) found in the crystal. Some notes about the code:
- Replace the stand-in values of *yourNeworkName* and *UrNtwrkP55word* with the credentials for your network
- You can change the positive negative thresholds of the  crystal (currently set to +/- 4%) by altering the *percent_contraint* variable to a different number. Keep in mind the light is constrained on a linear scale, so a high value would limit visibility for most states.
