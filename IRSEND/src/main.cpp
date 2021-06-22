#ifndef UNIT_TEST
#include <Arduino.h>
#endif
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ESP8266WiFi.h>
#include "EspMQTTClient.h"
#include "DHT.h"
#include <DHT_U.h>

#define DRD_TIMEOUT 10
#define DHTPIN 13
#define DHTTYPE DHT11

DHT_Unified dht(DHTPIN, DHTTYPE);

const uint16_t pino = 4;
IRsend irsend(pino);
int temp = 0;
int a = 0;

uint16_t rawData17[199] = {4356, 4422, 510, 1666, 510, 582, 510, 1646, 534, 1666, 510, 558, 534, 582, 508, 1666, 510, 584, 512, 578, 510, 1664, 510, 580, 510, 582, 510,
                           1666, 510, 1666, 510, 580, 510, 1670, 538, 1634, 510, 582, 508, 1670, 510, 1664, 510, 1666, 510, 1666, 510, 1664, 510, 1666, 512, 578, 510, 1668, 510, 582, 510,
                           580, 510, 582, 508, 582, 510, 580, 510, 584, 536, 528, 532, 580, 510, 580, 510, 558, 532, 582, 510, 556, 534, 580, 510, 558, 564, 1610, 534, 1664, 510, 1666,
                           510, 1666, 510, 1666, 510, 1666, 510, 1666, 510, 1666, 540, 5240, 4384, 4380, 510, 1666, 510, 580, 510, 1648, 530, 1664, 512, 582, 510, 580, 510, 1664, 510,
                           584, 538, 550, 510, 1666, 510, 580, 510, 580, 510, 1666, 510, 1666, 510, 582, 510, 1648, 562, 1634, 510, 580, 510, 1668, 510, 1666, 510, 1664, 510, 1664,
                           510, 1666, 510, 1644, 562, 550, 510, 1646, 532, 580, 512, 580, 510, 582, 510, 580, 510, 582, 508, 582, 540, 550, 510, 580, 510, 580, 510, 558, 532, 582,
                           510, 582, 510, 580, 510, 582, 538, 1634, 510, 1664, 510, 1666, 510, 1666, 510, 1640, 534, 1664, 510, 1666, 510, 1668, 510};

uint16_t rawData18[199] = {4380, 4402, 510, 1666, 510, 580, 510, 1670, 510, 1664, 510, 582, 508, 580, 510, 1640, 534, 584, 512, 554, 532, 1664, 510, 580, 510, 582, 510,
                           1666, 510, 1640, 536, 580, 510, 1670, 512, 1660, 510, 580, 510, 1668, 510, 1642, 534, 1666, 510, 1666, 510, 1664, 510, 1668, 512, 576, 510, 1646, 532, 580, 512, 580,
                           510, 580, 512, 580, 510, 580, 510, 560, 536, 554, 532, 580, 512, 580, 510, 1668, 510, 582, 510, 582, 510, 580, 510, 560, 534, 1660, 510, 1664, 510, 1664, 510, 582,
                           510, 1668, 510, 1640, 534, 1664, 510, 1666, 510, 5256, 4360, 4404, 510, 1664, 510, 582, 510, 1668, 510, 1664, 510, 556, 536, 580, 510, 1664, 510, 584, 512, 576,
                           510, 1664, 510, 582, 510, 582, 510, 1664, 510, 1664, 510, 582, 510, 1670, 512, 1660, 510, 582, 510, 1670, 510, 1664, 512, 1664, 510, 1664, 512, 1666, 510, 1642,
                           536, 576, 510, 1668, 510, 582, 510, 580, 510, 582, 510, 582, 510, 580, 510, 584, 512, 554, 532, 580, 510, 580, 510, 1668, 510, 580, 510, 582, 510, 580, 510, 582,
                           512, 1662, 510, 1666, 510, 1642, 532, 582, 510, 1644, 534, 1664, 512, 1664, 512, 1668, 508};

uint16_t rawData19[199] = {4388, 4358, 532, 1666, 510, 580, 510, 1668, 512, 1666, 562, 528, 510, 558, 532, 1666, 508, 584, 538, 528, 534, 1666, 510, 580, 510, 582, 510,
                           1664, 512, 1664, 512, 580, 510, 1670, 512, 1662, 510, 556, 534, 1670, 510, 1642, 532, 1666, 510, 1666, 510, 1666, 510, 1668, 512, 576, 510, 1668, 510, 560, 530,
                           580, 510, 582, 508, 558, 532, 580, 510, 582, 512, 578, 510, 582, 510, 1664, 510, 1666, 510, 556, 534, 582, 510, 580, 510, 582, 512, 1660, 510, 1664, 510, 582,
                           510, 580, 512, 1664, 510, 1664, 510, 1664, 510, 1666, 512, 5266, 4360, 4404, 510, 1642, 534, 580, 510, 1668, 510, 1664, 510, 558, 534, 558, 532, 1666, 508, 584,
                           512, 578, 510, 1662, 512, 580, 510, 558, 532, 1666, 510, 1666, 510, 580, 510, 1670, 512, 1660, 510, 582, 510, 1668, 510, 1642, 532, 1666, 510, 1666, 510, 1664,
                           510, 1666, 512, 576, 510, 1668, 510, 582, 510, 582, 508, 582, 510, 582, 510, 582, 510, 560, 560, 552, 510, 582, 510, 1666, 510, 1642, 532, 558, 532, 582, 510,
                           582, 508, 582, 538, 1634, 562, 1612, 512, 582, 562, 528, 510, 1666, 510, 1666, 510, 1666, 510, 1668, 512};

uint16_t rawData20[199] = {4396, 4404, 510, 1640, 536, 580, 510, 1668, 510, 1666, 510, 580, 510, 582, 510, 1664, 510, 582, 538, 550, 510, 1666, 510, 580, 510, 580,
                           510, 1666, 510, 1664, 512, 580, 510, 1670, 538, 1636, 510, 558, 532, 1670, 510, 1664, 510, 1666, 510, 1664, 510, 1664, 510, 1668, 538, 550, 512, 1668, 510,
                           582, 510, 582, 510, 580, 510, 582, 510, 580, 510, 560, 560, 552, 510, 582, 510, 1664, 510, 582, 510, 580, 510, 580, 510, 580, 510, 582, 538, 1638, 510,
                           1664, 510, 580, 510, 1670, 510, 1666, 510, 1664, 512, 1666, 510, 1666, 538, 5232, 4386, 4378, 510, 1666, 510, 580, 510, 1670, 510, 1664, 510, 580, 510,
                           580, 510, 1664, 510, 582, 514, 576, 510, 1664, 510, 580, 510, 582, 510, 1664, 510, 1666, 510, 582, 510, 1648, 534, 1660, 510, 582, 510, 1668, 510, 1664,
                           510, 1664, 510, 1640, 534, 1664, 510, 1666, 538, 550, 510, 1668, 512, 580, 510, 580, 510, 558, 532, 582, 510, 582, 510, 582, 538, 552, 510, 558, 534,
                           1664, 510, 582, 510, 582, 510, 580, 510, 580, 510, 582, 538, 1638, 510, 1642, 532, 580, 510, 1644, 534, 1664, 512, 1640, 534, 1664, 510, 1668, 510};

uint16_t rawData21[199] = {4380, 4398, 532, 1640, 536, 580, 510, 1668, 510, 1664, 510, 582, 510, 580, 510, 1642, 532, 582, 540, 528, 532, 1664, 510, 580, 510, 580,
                           510, 1664, 510, 1642, 534, 580, 510, 1670, 540, 1634, 510, 582, 510, 1670, 510, 1666, 510, 1666, 510, 1664, 510, 1664, 510, 1666, 538, 550, 512, 1668, 510, 582,
                           508, 556, 536, 580, 510, 556, 534, 580, 510, 560, 562, 550, 510, 1670, 510, 1664, 510, 582, 510, 582, 510, 580, 510, 558, 534, 582, 512, 1664, 512, 580, 510,
                           580, 512, 1662, 512, 1664, 510, 1640, 536, 1664, 510, 1664, 540, 5208, 4406, 4378, 510, 1664, 510, 580, 510, 1670, 510, 1664, 510, 580, 510, 582, 510, 1664,
                           510, 584, 538, 548, 512, 1642, 534, 580, 510, 582, 510, 1666, 510, 1666, 510, 582, 510, 1670, 622, 1552, 510, 580, 510, 1668, 510, 1666, 510, 1644, 532,
                           1666, 510, 1664, 510, 1668, 538, 528, 532, 1670, 508, 582, 510, 580, 510, 558, 534, 582, 510, 558, 534, 580, 514, 576, 510, 1668, 510, 1666, 510, 582,
                           510, 580, 510, 556, 534, 580, 510, 584, 564, 1612, 512, 580, 620, 448, 534, 1664, 510, 1666, 510, 1666, 510, 1666, 510, 1668, 510};

uint16_t rawData22[199] = {4382, 4410, 510, 1664, 510, 580, 512, 1668, 510, 1664, 512, 580, 510, 580, 510, 1664, 510, 584, 512, 576, 510, 1664, 510, 580, 512, 580,
                           510, 1664, 512, 1664, 510, 580, 510, 1670, 512, 1660, 510, 580, 510, 1670, 510, 1662, 512, 1664, 510, 1664, 512, 1666, 510, 1668, 512, 576, 510, 1668, 510, 580,
                           510, 558, 532, 580, 510, 580, 510, 580, 510, 582, 512, 576, 510, 1668, 512, 1664, 510, 1664, 510, 580, 510, 580, 512, 580, 510, 582, 512, 1660, 512, 580, 510,
                           582, 510, 582, 510, 1668, 510, 1664, 512, 1664, 510, 1640, 538, 5256, 4358, 4402, 512, 1664, 512, 556, 534, 1668, 510, 1666, 510, 580, 510, 580, 510, 1664,
                           510, 582, 512, 576, 510, 1664, 510, 582, 510, 582, 510, 1664, 512, 1664, 510, 580, 510, 1670, 512, 1660, 512, 580, 510, 1668, 510, 1664, 510, 1664, 510,
                           1642, 532, 1666, 510, 1666, 512, 576, 512, 1646, 534, 580, 510, 580, 510, 580, 510, 580, 510, 580, 510, 582, 512, 578, 510, 1668, 510, 1664, 510, 1664,
                           510, 558, 534, 580, 510, 580, 510, 582, 512, 1660, 512, 556, 532, 582, 510, 580, 510, 1646, 532, 1666, 510, 1664, 510, 1668, 510};

uint16_t rawData23[199] = {4408, 4384, 510, 1664, 510, 582, 510, 1646, 532, 1664, 510, 582, 510, 580, 510, 1664, 510, 584, 538, 550, 510, 1664, 510, 582, 510, 582,
                           510, 1664, 510, 1666, 510, 580, 510, 1650, 534, 1660, 510, 582, 510, 1668, 512, 1664, 510, 1664, 510, 1666, 510, 1664, 512, 1666, 538, 550, 510, 1668, 510, 582,
                           510, 580, 510, 580, 510, 582, 510, 582, 510, 582, 538, 550, 510, 1668, 512, 580, 510, 1670, 510, 556, 534, 582, 510, 580, 510, 582, 538, 1636, 510, 580, 510,
                           1670, 510, 580, 510, 1668, 510, 1666, 510, 1642, 534, 1666, 538, 5224, 4384, 4358, 532, 1666, 510, 580, 510, 1668, 510, 1666, 510, 582, 510, 580, 510, 1642,
                           534, 584, 538, 550, 510, 1666, 510, 580, 510, 582, 510, 1664, 510, 1666, 510, 580, 510, 1670, 538, 1612, 534, 582, 510, 1668, 510, 1642, 534, 1664, 510, 1644,
                           532, 1666, 510, 1668, 538, 550, 510, 1670, 508, 582, 510, 580, 512, 558, 534, 580, 510, 582, 510, 582, 540, 526, 532, 1668, 510, 558, 534, 1670, 510, 556,
                           534, 580, 510, 580, 510, 582, 540, 1636, 510, 580, 512, 1646, 534, 582, 510, 1668, 510, 1666, 510, 1666, 510, 1668, 510};

uint16_t rawData24[199] = {4358, 4398, 534, 1664, 510, 582, 510, 1670, 510, 1640, 534, 580, 510, 580, 510, 1664, 510, 560, 560, 550, 510, 1666, 508, 582, 510, 580,
                           510, 1664, 510, 1666, 508, 582, 510, 1672, 540, 1612, 532, 582, 510, 1670, 510, 1664, 510, 1664, 510, 1666, 510, 1666, 510, 1668, 514, 576, 510, 1670, 510, 580,
                           510, 580, 512, 580, 510, 580, 510, 580, 510, 582, 538, 550, 512, 1668, 510, 580, 510, 580, 510, 582, 510, 580, 510, 580, 510, 582, 538, 1610, 534, 582, 510,
                           1670, 510, 1666, 510, 1664, 510, 1666, 510, 1664, 510, 1644, 562, 5230, 4386, 4378, 510, 1642, 532, 580, 510, 1668, 512, 1666, 510, 580, 510, 580, 510, 1662,
                           514, 582, 538, 552, 510, 1664, 510, 580, 510, 580, 510, 1664, 510, 1666, 510, 582, 510, 1670, 538, 1612, 532, 580, 510, 1670, 510, 1666, 510, 1664, 510, 1666,
                           510, 1666, 510, 1668, 538, 550, 510, 1670, 510, 582, 510, 582, 508, 582, 510, 580, 510, 580, 512, 582, 538, 552, 510, 1646, 534, 582, 510, 558, 532, 580,
                           510, 580, 510, 582, 510, 584, 538, 1634, 510, 580, 512, 1668, 510, 1664, 510, 1664, 512, 1664, 512, 1640, 536, 1668, 510};

uint16_t rawData25[199] = {4410, 4366, 532, 1666, 510, 580, 510, 1670, 510, 1664, 512, 580, 510, 580, 512, 1664, 510, 560, 562, 548, 512, 1640, 534, 580, 512, 580,
                           510, 1664, 510, 1644, 532, 582, 510, 1670, 538, 1636, 510, 556, 534, 1670, 510, 1664, 510, 1640, 534, 1666, 510, 1666, 510, 1668, 512, 576, 510, 1670, 510,
                           580, 510, 556, 536, 580, 512, 582, 510, 580, 510, 584, 538, 1634, 510, 1666, 510, 580, 510, 582, 508, 582, 510, 582, 510, 582, 510, 582, 540, 550, 510,
                           556, 534, 1666, 510, 1666, 510, 1666, 510, 1666, 510, 1664, 512, 1638, 538, 5244, 4410, 4378, 510, 1666, 512, 578, 512, 1670, 510, 1666, 510, 558, 532,
                           582, 510, 1666, 510, 582, 538, 552, 510, 1664, 512, 580, 510, 582, 508, 1666, 510, 1666, 510, 582, 510, 1670, 540, 1634, 510, 556, 534, 1668, 510, 1664,
                           512, 1640, 534, 1642, 534, 1642, 534, 1666, 540, 550, 510, 1670, 510, 580, 510, 580, 510, 580, 512, 580, 510, 580, 510, 582, 540, 1632, 512, 1666, 510,
                           580, 510, 580, 510, 580, 510, 582, 510, 556, 534, 582, 540, 550, 510, 558, 534, 1664, 538, 1636, 512, 1666, 510, 1664, 510, 1666, 510, 1668, 510};

uint16_t rawData26[199] = {4380, 4422, 510, 1666, 510, 580, 510, 1668, 512, 1664, 510, 580, 510, 558, 534, 1666, 510, 584, 538, 550, 510, 1664, 510, 580, 512, 580,
                           510, 1664, 510, 1664, 510, 580, 510, 1672, 538, 1634, 510, 582, 510, 1668, 510, 1666, 510, 1666, 510, 1664, 510, 1664, 510, 1668, 540, 550, 510, 1668, 510,
                           582, 510, 582, 510, 582, 510, 580, 510, 582, 508, 582, 540, 1634, 510, 1664, 510, 558, 532, 1668, 510, 582, 510, 580, 510, 580, 510, 560, 562, 550, 512,
                           580, 510, 1666, 510, 580, 510, 1668, 510, 1664, 510, 1664, 510, 1642, 560, 5232, 4386, 4356, 534, 1666, 510, 582, 508, 1670, 510, 1666, 510, 580, 510,
                           582, 510, 1666, 510, 582, 538, 552, 510, 1666, 510, 582, 510, 580, 510, 1642, 534, 1666, 510, 582, 510, 1672, 540, 1634, 510, 582, 510, 1668, 510,
                           1666, 510, 1664, 510, 1666, 510, 1664, 510, 1668, 538, 528, 532, 1668, 510, 582, 510, 582, 510, 580, 510, 580, 510, 582, 510, 582, 538, 1636, 510,
                           1666, 508, 582, 510, 1668, 510, 580, 510, 580, 510, 582, 510, 582, 540, 548, 512, 580, 510, 1664, 512, 558, 532, 1670, 510, 1664, 510, 1666,
                           510, 1668, 510};

uint16_t rawData27[199] = {4442, 4322, 512, 1664, 510, 580, 510, 1668, 510, 1666, 510, 580, 510, 582, 510, 1664, 510, 582, 540, 526, 532, 1644, 532, 580, 510,
                           582, 510, 1666, 510, 1664, 510, 582, 510, 1670, 540, 1634, 510, 580, 510, 1668, 510, 1666, 510, 1666, 510, 1664, 512, 1664, 510, 1666, 540, 550, 510, 1670,
                           510, 580, 510, 580, 510, 558, 532, 580, 510, 580, 510, 582, 540, 1634, 512, 580, 510, 580, 510, 1664, 510, 558, 534, 580, 512, 580, 510, 582, 514, 576,
                           510, 1670, 508, 1666, 510, 556, 536, 1670, 510, 1664, 510, 1664, 510, 1664, 538, 5232, 4384, 4356, 534, 1666, 510, 580, 510, 1670, 510, 1640, 536, 582,
                           510, 580, 510, 1664, 512, 560, 618, 492, 510, 1664, 510, 558, 532, 580, 512, 1640, 534, 1666, 510, 580, 510, 1672, 538, 1634, 510, 582, 536, 1620, 532,
                           1666, 510, 1666, 508, 1666, 510, 1664, 510, 1666, 540, 526, 534, 1668, 510, 556, 534, 580, 510, 580, 512, 556, 534, 582, 510, 582, 540, 1634, 538,
                           554, 510, 582, 510, 1666, 510, 580, 510, 582, 510, 558, 532, 584, 538, 550, 510, 1668, 510, 1664, 536, 554, 510, 1646, 532, 1666, 510, 1666,
                           510, 1668, 510};

uint16_t rawData28[199] = {4410, 4378, 510, 1666, 510, 556, 534, 1670, 510, 1664, 510, 580, 510, 580, 510, 1666, 510, 584, 510, 576, 512, 1664, 510, 580, 510,
                           580, 512, 1664, 510, 1664, 512, 580, 512, 1670, 512, 1662, 510, 580, 510, 1670, 510, 1664, 510, 1664, 512, 1664, 510, 1666, 510, 1668, 512, 578, 510,
                           1668, 510, 580, 510, 580, 510, 582, 510, 582, 510, 580, 512, 582, 514, 1660, 510, 580, 510, 582, 510, 580, 510, 582, 510, 580, 512, 580, 510, 582,
                           538, 550, 510, 1664, 510, 1664, 512, 1664, 512, 1664, 510, 1666, 510, 1666, 510, 1666, 512, 5242, 4408, 4380, 510, 1668, 508, 582, 510, 1668, 510,
                           1666, 510, 580, 510, 580, 512, 1664, 510, 582, 536, 552, 512, 1666, 510, 580, 510, 580, 512, 1666, 510, 1666, 510, 580, 510, 1672, 512, 1662,
                           510, 580, 510, 1670, 510, 1666, 510, 1664, 510, 1664, 512, 1666, 508, 1668, 512, 576, 510, 1670, 510, 580, 510, 582, 510, 582, 510, 582, 510,
                           580, 510, 582, 512, 1662, 510, 580, 510, 580, 510, 580, 510, 580, 512, 580, 510, 580, 510, 584, 538, 552, 510, 1664, 510, 1644, 532, 1666,
                           510, 1664, 510, 1664, 510, 1644, 532, 1668, 510};

uint16_t rawData29[199] = {4410, 4392, 510, 1664, 510, 582, 510, 1668, 510, 1664, 510, 580, 510, 580, 510, 1664, 510, 558, 564, 548, 510, 1666, 510, 582, 510,
                           580, 512, 1642, 534, 1666, 510, 580, 510, 1672, 538, 1634, 510, 580, 510, 1668, 512, 1664, 510, 1664, 510, 1644, 532, 1664, 510, 1668, 538, 526, 534,
                           1648, 532, 580, 510, 558, 532, 580, 510, 582, 564, 526, 510, 582, 540, 1634, 510, 558, 534, 1670, 510, 556, 534, 582, 510, 558, 532, 582, 510, 582,
                           538, 550, 510, 1664, 510, 582, 510, 1670, 510, 1664, 510, 1664, 510, 1664, 510, 1666, 538, 5208, 4410, 4354, 534, 1664, 510, 582, 508, 1646, 532,
                           1644, 532, 582, 510, 580, 510, 1666, 510, 582, 538, 550, 508, 1666, 510, 582, 510, 580, 510, 1666, 510, 1664, 510, 580, 510, 1670, 540, 1634,
                           510, 580, 510, 1668, 510, 1664, 510, 1664, 510, 1666, 510, 1666, 510, 1666, 540, 526, 532, 1668, 510, 556, 534, 580, 510, 582, 510, 580, 510,
                           560, 532, 582, 540, 1632, 510, 582, 508, 1670, 510, 558, 534, 580, 510, 580, 510, 556, 534, 584, 540, 528, 532, 1666, 510, 582, 510, 1670,
                           510, 1664, 510, 1666, 510, 1664, 510, 1668, 510};

uint16_t rawData30[199] = {4354, 4404, 532, 1664, 510, 582, 510, 1670, 510, 1640, 536, 580, 510, 580, 512, 1664, 510, 582, 540, 550, 510, 1664, 510, 558, 534, 580,
                           510, 1666, 510, 1666, 510, 580, 512, 1670, 538, 1636, 510, 580, 510, 1670, 510, 1664, 512, 1664, 512, 1666, 510, 1642, 534, 1668, 538, 550, 510, 1670, 510,
                           580, 510, 582, 510, 580, 510, 582, 510, 580, 512, 560, 562, 1634, 510, 582, 510, 1670, 538, 1638, 510, 580, 510, 582, 510, 580, 510, 584, 538, 550, 510,
                           1668, 510, 582, 510, 556, 536, 1664, 510, 1642, 534, 1664, 512, 1664, 538, 5232, 4386, 4378, 510, 1666, 510, 582, 536, 1642, 510, 1664, 510, 580, 510, 580,
                           510, 1664, 510, 584, 538, 550, 510, 1664, 510, 582, 510, 582, 510, 1664, 510, 1664, 510, 580, 510, 1670, 542, 1632, 512, 580, 510, 1646, 532, 1664, 510,
                           1666, 510, 1666, 508, 1666, 510, 1668, 538, 550, 510, 1670, 510, 556, 534, 580, 512, 580, 536, 554, 510, 580, 510, 582, 540, 1632, 510, 580, 512, 1668,
                           510, 1664, 510, 558, 532, 582, 510, 580, 510, 582, 540, 528, 534, 1666, 512, 560, 532, 580, 510, 1664, 512, 1664, 510, 1664, 510, 1668, 510};

uint16_t rawData55[199] = {4410, 4390, 510, 1644, 530, 582, 510, 1668, 510, 1666, 510, 582, 508, 562, 530, 1666, 510, 562, 562, 548, 510, 1666, 508, 562, 530,
                           582, 510, 1644, 530, 1664, 510, 582, 510, 1670, 542, 548, 510, 1670, 508, 1666, 510, 1666, 510, 1664, 510, 580, 510, 1668, 510, 1646, 564, 1630, 512,
                           582, 508, 558, 532, 580, 512, 582, 508, 1664, 512, 582, 510, 582, 544, 1608, 532, 1664, 510, 1666, 510, 582, 510, 580, 510, 560, 532, 582, 510, 582,
                           542, 546, 510, 582, 508, 560, 532, 1666, 510, 1664, 512, 1664, 510, 1642, 532, 1666, 542, 5234, 4388, 4354, 532, 1664, 510, 582, 510, 1670, 510, 1666,
                           510, 580, 510, 580, 510, 1642, 534, 582, 544, 544, 510, 1662, 512, 560, 532, 556, 536, 1664, 510, 1664, 510, 580, 510, 1672, 568, 522, 510, 1668,
                           512, 1644, 532, 1664, 510, 1664, 510, 582, 510, 1648, 530, 1666, 568, 1582, 534, 580, 510, 582, 510, 582, 510, 580, 510, 1644, 532, 580, 510,
                           582, 566, 1606, 512, 1642, 532, 1664, 510, 580, 510, 580, 510, 558, 532, 558, 532, 584, 542, 546, 510, 580, 510, 580, 510, 1664, 510, 1664,
                           510, 1666, 510, 1644, 530, 1668, 512};
// Wifi configuration
const char *ssid = "AlaKlein";
const char *password = "yrl4771*";

void wifiConnect()
{
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  Serial.println(WiFi.localIP());
}

EspMQTTClient client(
    "AlaKlein",
    "yrl4771*",
    "192.168.2.248",
    "node",
    1883);

void onConnectionEstablished()
{
  client.subscribe(WiFi.localIP().toString() + "/controller", [](const String &payload)
                   {
                     Serial.println(payload);
                     temp = payload.toInt();
                     if (temp == 17)
                     {
                       irsend.sendRaw(rawData17, 199, 38);
                       temp = 0;
                     }
                     else if (temp == 18)
                     {
                       irsend.sendRaw(rawData18, 199, 38);
                       temp = 0;
                     }
                     else if (temp == 19)
                     {
                       irsend.sendRaw(rawData19, 199, 38);
                       temp = 0;
                     }
                     else if (temp == 20)
                     {
                       irsend.sendRaw(rawData20, 199, 38);
                       temp = 0;
                     }
                     else if (temp == 21)
                     {
                       irsend.sendRaw(rawData21, 199, 38);
                       temp = 0;
                     }
                     else if (temp == 22)
                     {
                       irsend.sendRaw(rawData22, 199, 38);
                       temp = 0;
                     }
                     else if (temp == 23)
                     {
                       irsend.sendRaw(rawData23, 199, 38);
                       temp = 0;
                     }
                     else if (temp == 24)
                     {
                       irsend.sendRaw(rawData24, 199, 38);
                       temp = 0;
                     }
                     else if (temp == 25)
                     {
                       irsend.sendRaw(rawData25, 199, 38);
                       temp = 0;
                     }
                     else if (temp == 26)
                     {
                       irsend.sendRaw(rawData26, 199, 38);
                       temp = 0;
                     }
                     else if (temp == 27)
                     {
                       irsend.sendRaw(rawData27, 199, 38);
                       temp = 0;
                     }
                     else if (temp == 28)
                     {
                       irsend.sendRaw(rawData28, 199, 38);
                       temp = 0;
                     }
                     else if (temp == 29)
                     {
                       irsend.sendRaw(rawData29, 199, 38);
                       temp = 0;
                     }
                     else if (temp == 30)
                     {
                       irsend.sendRaw(rawData30, 199, 38);
                       temp = 0;
                     }
                     else if (temp == 55)
                     {
                       irsend.sendRaw(rawData55, 199, 38);
                       temp = 0;
                     }
                   });
}

void setup()
{
  Serial.begin(9600);
  wifiConnect();
  irsend.begin();
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
}

void loop()
{
  client.loop();
  delay(5000);
  sensors_event_t eventT;
  sensors_event_t eventH;
  dht.temperature().getEvent(&eventT);
  dht.humidity().getEvent(&eventH);
  client.publish(WiFi.localIP().toString() + "/sensor", (String)eventT.temperature + ";" + (String)eventH.relative_humidity);
}