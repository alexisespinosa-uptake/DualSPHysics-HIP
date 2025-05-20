#!/bin/bash

# Setting environment for different clusters
case "$HOSTNAME" in
    *setonix*)
	echo "Setting environment for Setonix"
	module load cpe/24.07
	module swap pawseyenv/2024.05 pawseyenv/2025.03
        module load gcc-native/13.2
        module load rocm/6.2.4
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

