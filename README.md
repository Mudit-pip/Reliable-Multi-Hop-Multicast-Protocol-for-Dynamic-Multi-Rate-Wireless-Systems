# Reliable Multi-Hop Multicast Routing for Dynamic Multi-Rate Wireless Systems

A multicast routing approach for wireless multi-hop networks that considers link reliability, varying transmission rates, and forwarding-node selection.

## Overview

Wireless multi-hop networks can suffer from packet loss, changing link quality, and different transmission rates across links. Traditional single-path routing may continue using a poor link even when other nearby nodes could receive and forward the packet.

This project develops a multirate multicast routing approach using **ETX** and **ETT** to evaluate transmission cost and select suitable forwarding strategies.

## Key Features

- ETX-based link cost evaluation
- ETT calculation using link transmission rates
- Multicast routing from one source to multiple destinations
- Multiple forwarder evaluation
- Forwarder-set selection using transmission cost
- Packet-level simulation for evaluating routing behavior

## Routing Approach

The algorithm evaluates different packet reception outcomes when multiple forwarders are available:

1. Neither forwarder receives the packet
2. Only forwarder 1 receives the packet
3. Only forwarder 2 receives the packet
4. Both forwarders receive the packet

The expected transmission cost is calculated from the probability and cost of each case.

## ETX and ETT

### ETX

Expected Transmission Count (ETX) represents the expected number of transmissions required for successful packet delivery.

### ETT

Expected Transmission Time (ETT) extends the cost calculation by considering the transmission rate of the links.

```text
ETX → expected transmission count
ETT → expected transmission time considering link rate
````

## Forwarder Set Selection

For multicast routing, multiple intermediate nodes can act as possible forwarders.

The algorithm evaluates different forwarding strategies and selects the one with the minimum estimated transmission cost.

Example:

```text
Source
  |
  +----> Forwarder 1 ----> Destination 1
  |                    \
  |                     --> Destination 2
  |
  +----> Forwarder 2 ----> Destination 1
                       \
                        --> Destination 2
```

## Simulation

A packet-level simulation was used to evaluate the routing approach.

The simulation considers:

* Packet generation
* Packet transmission
* Packet forwarding
* Packet reception
* Packet loss
* Packet collisions

The simulation measures:

* Destination packets
* Source transmissions
* Transmission cost
* Error percentage

## Results

### Single Source → Single Destination

* Minimum ETT Cost: `2.5`
* Destination Packets: `100,000`
* Source Transmissions: `249,659`
* Error Percentage: `0.4%`

### Single Source → Two Destinations

* Minimum ETT Cost: `2.475`
* Destination Packets: `100,000`
* Source Transmissions: `241,654`
* Error Percentage: `2.36%`

## Project Concepts

* Wireless Multi-Hop Networks
* Multicast Routing
* Opportunistic Routing
* ETX
* ETT
* Forwarder Set Selection
* Packet-Level Simulation

```

This is the **raw Markdown code** you can paste directly into `README.md`.
```
