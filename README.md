# adsb-plot

Plots the position and altitude information in [SBS-1 format](http://woodair.net/sbs/article/barebones42_socket_data.htm) [ADS-B](https://www.sigidwiki.com/wiki/Automatic_Dependent_Surveillance-Broadcast_(ADS-B)) messages into a pretty image. These messages can be received from aircraft using [dump1090](https://github.com/flightaware/dump1090) / [readsb](https://github.com/Mictronics/readsb-protobuf) and a software-defined radio, such as an [RTL-SDR](https://rtl-sdr.com/) or [Airspy](https://airspy.com/). Each pair of coordinates received is plotted as a pixel, with its colour representing altitude.

Currently the latitude and longitudes are converted to x and y coordinates with a simple constant scaling, with no compensation for the Earth’s curvature. Basically that means the plane tracks plotted by this program will appear more horizontally stretched at higher latitudes.

![Plotted image](sample.png)

## Compiling

- Install png++.
- `git clone` this repository.
- Install Tup and run `tup` in the cloned repo.

## My receiver setup for your reference

```
  |  SMA Male-Male +---------------+ 5m RG58 +------------+ USB Type-C to Type-A +--------+
 /|\===============| TQP3M9009 LNA |=========| RTL-SDR V3 |======================| Laptop |
                   +---------------+         +------------+                      +--------+
```

The antenna is a quarter wave ground plane antenna designed with [M0UKD’s calculator](https://m0ukd.com/calculators/quarter-wave-ground-plane-antenna-calculator/). On the laptop dump1090 processes the received ADS-B signals and netcat is used to extract the data in SBS-1 format:

- `dump1090 --gain 25 --net --fix --metric`
- `nc localhost 30003 | tee --append adsb.csv`

