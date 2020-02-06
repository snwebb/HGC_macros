# Plotting Macros for HGCal

## Introduction

To compile type `make`

The code is located the `src` directory.
Each task-type is in a separate .cxx file, in the same `HGC` class.
Choose the plot to make in the `HGC.cxx` file.

Response plots are found in `C3D_histo_jet.cxx` 
Resolution plots are found in `effRMS.cxx`
Plot an event display using `PlotterEventDisplay.cxx`

## Running the resolution, efficiency and rate plots

To run do:

```./HGC --outdir out --config configs/default.json```

where the user sets the output directory and the input config file.