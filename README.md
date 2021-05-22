# adsb-plot

Plots the position and altitude information in [SBS-1 format](http://woodair.net/sbs/article/barebones42_socket_data.htm) [ADS-B](https://www.sigidwiki.com/wiki/Automatic_Dependent_Surveillance-Broadcast_(ADS-B)) messages into a pretty image. These messages can be received from aircraft using a software-defined radio, such as an [RTL-SDR](https://rtl-sdr.com/) or [Airspy](https://airspy.com/), and [dump1090](https://github.com/flightaware/dump1090) / [readsb](https://github.com/Mictronics/readsb-protobuf). Each pair of coordinates received is plotted as a pixel, with its colour representing altitude.

Currently the latitudes and longitudes are converted to x and y coordinates through a simple constant scaling, with no compensation for the Earth’s curvature. Effectively this means the tracks plotted by this program will appear more horizontally stretched at higher latitudes.

![Plotted image](sample.png)

## Compiling

- Install png++.
- `git clone` this repository.
- Install Tup and run `tup` in the cloned repo. Alternatively, run `c++ --std=c++17 -O2 -lpng *.cpp -o adsb-plot`.

## My receiver setup for reference

```
  |  N Male - SMA Male +---------------+ 5 m RG-58 +------------+ USB Type-A to Type-C +--------+
 /|\===================| TQP3M9009 LNA |===========| RTL-SDR V3 |======================| Laptop |
                       +---------------+           +------------+                      +--------+
```

The antenna is a quarter wave ground plane antenna designed with [M0UKD’s calculator](https://m0ukd.com/calculators/quarter-wave-ground-plane-antenna-calculator/), built with a chassis mount female N connector and 1.25 mm diameter copper wire. It hangs out from a second-floor window facing London Heathrow Airport. On the laptop, dump1090 processes the received ADS-B signals and netcat is used to extract the data from dump1090 in SBS-1 format:

- `dump1090 --gain 25 --net --fix --metric`
- `nc localhost 30003 | tee --append adsb.csv`

The image above was produced from 4.9 GiB of data recorded in IO91UB on and off over a week. You might be able to spot London Heathrow, London Gatwick and Redhill Airport!
