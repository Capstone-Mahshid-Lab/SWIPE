# -*- coding: utf-8 -*-
"""
Created on Mon Nov 11 18:56:48 2024

@author: Dell
"""

#Need to turn on bluetooth for this to work
import asyncio
from bleak import BleakScanner

async def main():
    devices = await BleakScanner.discover()
    for d in devices:
        print(d)

asyncio.run(main())


""" import asyncio
from bleak import BleakClient

address = "53:4D:4E:5E:F2:55"
MODEL_NBR_UUID = "2A24"

async def main(address):
    async with BleakClient(address) as client:
        model_number = await client.read_gatt_char(MODEL_NBR_UUID)
        print("Model Number: {0}".format("".join(map(chr, model_number))))

asyncio.run(main(address)) """


