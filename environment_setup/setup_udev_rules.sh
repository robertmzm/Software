#!/bin/bash

# Save the parent dir of this script since we want to return here
# so that commands are run relative to the location of this script. This
# helps prevent bugs and odd behaviour if this script is run through a symlink
# or from a different directory.
CURR_DIR=$(dirname -- "$(readlink -f -- "$BASH_SOURCE")")
cd $CURR_DIR

# Set up udev rules for USB permissions. This gives the user the required permissions
# to use the radio dongle and flash the robots via USB.
echo "================================================================"
echo "Setting up Thunderbots udev rules"
echo "================================================================"
# Target file directory
udev_rules_file="/etc/udev/rules.d/99-thunderbots.rules"

# Copy the new Thunderbots udev rules to the rule folder, overwriting any
# existing files
sudo cp $CURR_DIR/99-thunderbots.rules $udev_rules_file
if [ $? -ne 0 ]; then
    echo "##############################################################"
    echo "Error: Failed to copy udev rules"
    echo "##############################################################"
    exit 1
fi

echo "================================================================"
echo "Done"
echo ""
echo "Make sure to log out and log back in for permissions changes to take effect!"
echo "================================================================"

