#!/bin/bash

# Setting environment for different clusters
case "$HOSTNAME" in
    *setonix*)
	echo "Setting environment for Setonix"
        module load rocm/5.6.1
        module load craype-accel-amd-gfx90a
	module list
        ;;
    *cluster2*)
        # Configuration for another cluster
        ;;
    # Add more cases as needed
    *)
        echo "Unknown cluster: $HOSTNAME"
        ;;
esac

