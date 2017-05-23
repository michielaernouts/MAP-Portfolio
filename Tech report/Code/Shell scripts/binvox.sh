#!/bin/bash
read -p "Enter the .stl file that you want to use: " -i "$HOME/" -e path
echo $path

cd ~/binvox
./binvox $path -e -ri

