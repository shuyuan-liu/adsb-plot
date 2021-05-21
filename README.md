# adsb-plot

Reads prerecorded ADS-B data in [SBS-1 format](http://woodair.net/sbs/article/barebones42_socket_data.htm) and plots an image. Each message containing latitude, longitude and altitude is plotted as a pixel, with its colour representing altitude.

![Sample plotted image](sample.png)

## Compiling

- Install png++.
- `git clone` the repository.
- Install Tup and run `tup` in the cloned repo.

