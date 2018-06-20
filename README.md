# CRYPT0MANIA
## This is the repository for everything related to the CRYPT0MANIA project
![](images/crystal-img.JPG)

Cryptomania is a sculpture designed as commentary on the cryptocurrency pandemonium. It lights up based on the 1 hour price change (a percentage value) of a particular crypto-currency – Ethereum.

This project was created in Fall 2017, at the height of crypto pandemonium. Since then it has been demo'd at various expositions.

| ![](images/ITPWinterShow2017.JPG)| ![](images/BMCC.JPG)| ![](images/MiniMakerFaire.JPG) |
| :---: |:---:| :---:|
| [2017 ITP Winter Show](https://itp.nyu.edu/shows/winter2017/crypt0mania/) | [2018 BMCC MakerSpace](http://www.bmcc.cuny.edu/calendar/events.jsp?id=34447) | [2018 MakerFaire Philadelphia](https://philly.makerfaire.com/maker/entry/83/)

Details on it can be found [here](http://www.blog.calebfergie.com/2017/12/29/api-to-led-8/), with more detail on the code [here](http://www.blog.calebfergie.com/2017/12/21/api-to-led-6/).

The crystal still lives and breathes with data. The data it is recieving can be found on it's [live feed website](http://sandbox.calebfergie.com:8080/), which is currently a WIP.

## Notes about this repository

Arguably the most important file in this repo is the **[WeMos code](https://github.com/calebfergie/CRYPT0MANIA/blob/master/weMos_code.ino)**. The WeMos device is the microcontroller (i.e. knockoff Arduino) found in the crystal. Some notes about the code:
- Replace the stand-in values of *yourNeworkName* and *UrNtwrkP55word* with the credentials for your network
- You can change the positive negative thresholds of the  crystal (currently set to +/- 4%) by altering the *percent_contraint* variable to a different number. Keep in mind the light is constrained on a linear scale, so a high value would limit visibility for most states.
- The range of the price change (currently set to 1-hour) can be altered to a 24-hours or even 7-days by changing the *startingVal* variable (currently set to "percent_change_1h"). The crystal parses information from [CoinMarketCap](https://coinmarketcap.com/api/), specifically [this page: https://api.coinmarketcap.com/v1/ticker/ethereum/](https://api.coinmarketcap.com/v1/ticker/ethereum/) - so to change the range, input one of the keys listed.
