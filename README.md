# CRYPT0MANIA
[![](images/video-screenshot.png)](https://vimeo.com/249122914)

⬆️Click for Video⬆️


CRYPT0MANIA is a sculpture designed as commentary on the cryptocurrency pandemonium. It lights up based on the 1 hour price change (a percentage value) of a particular crypto-currency – Ethereum.

The crystal is intended to encapsulate the mania by showing an ambiguous, but real time indication “good” or “bad” sentiment. The sculpture is intended to call the following concepts for consideration:

- The **hive-mind mentality** of observing a price as a proxy for “real” value
- The **populist and over-simplified** media coverage of blockchain technology
- The **shortsighted, accelerationist** nature of cryptocurrency discourse and “technical analysis” by so-called experts

The crystal is a passive object that pulses with varying intensity and direction over time.

![https://makerfaire.com/maker/entry/67572/](images/editors-choice-banner.png)

CRYPTOMANIA contains an internet-connected circuit that calls [this API](https://api.coinmarketcap.com/v1/ticker/ethereum/) to retrieve price change information and convert it into a more abstract and emotional glowing digital signal.

This project was created in Fall 2017, at the height of crypto pandemonium. Since then, cryptocurrency has fallen out of the mainstream media hype cycle; **Yet the mania remains encapsulated within the crystal.** CRYPT0MANIA has been demo'd at various expositions since 2017:

| ![](images/ITPWinterShow2017.JPG)| ![](images/BMCC.JPG)| ![](images/MiniMakerFaire.JPG) | ![](images/NYCML2018.png) |![](images/2018NYCmaker.png) |
| :---: |:---:| :---:| :---:| :---:|
| [2017 ITP Winter Show](https://itp.nyu.edu/shows/winter2017/crypt0mania/) | [2018 BMCC MakerSpace](http://www.bmcc.cuny.edu/calendar/events.jsp?id=34447) | [2018 MakerFaire Philadelphia](https://philly.makerfaire.com/maker/entry/83/) | [2018 NYC Media Lab Summit](https://www.summit.nycmedialab.org/demo-expo/#CREATIVE) | [2018 World Maker Faire](https://makerfaire.com/maker/entry/67572/) |

### Further details on it can be found [here](http://www.blog.calebfergie.com/2017/12/29/api-to-led-8/), with more detail on the code [here](http://www.blog.calebfergie.com/2017/12/21/api-to-led-6/).

## Notes about this repository

Arguably the most important file in this repo is the **[WeMos code](https://github.com/calebfergie/CRYPT0MANIA/blob/master/weMos_code.ino)**. The WeMos device is the microcontroller (i.e. knockoff Arduino) found in the crystal. Some notes about the code:
- Replace the stand-in values of *yourNeworkName* and *UrNtwrkP55word* with the credentials for your network
- You can change the positive negative thresholds of the  crystal (currently set to +/- 4%) by altering the *percent_contraint* variable to a different number. Keep in mind the light is constrained on a linear scale, so a high value would limit visibility for most states.
- The range of the price change (currently set to 1-hour) can be altered to a 24-hours or even 7-days by changing the *startingVal* variable (currently set to "percent_change_1h"). The crystal parses information from [CoinMarketCap](https://coinmarketcap.com/api/), specifically [this page: https://api.coinmarketcap.com/v1/ticker/ethereum/](https://api.coinmarketcap.com/v1/ticker/ethereum/) - so to change the range, input one of the keys listed.
