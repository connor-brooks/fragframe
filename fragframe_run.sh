#!/bin/bash
echo "Starting fragframe..."
ls shader.frag | entr -r ./_fragframe
