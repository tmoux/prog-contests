#!/bin/bash

dat=$(date +"%D")
git add .
git commit -m "$dat"
git push origin master
