#!/bin/bash
set -eo pipefail
HOME=/Users/anka
VERSION=3
# Commands from the documentation are inserted right below this line
# Anything below here is exclusive to our CI/CD
## Cleanup EOSIO.CDT directory 
cd ~ && rm -rf ${EOSIO_CDT_LOCATION}
## Needed for State History Plugin Test
brew install nvm && mkdir ~/.nvm && echo "export NVM_DIR=~/.nvm" >> ~/.bash_profile && echo "source \$(brew --prefix nvm)/nvm.sh" >> ~/.bash_profile && cat ~/.bash_profile && source ~/.bash_profile && echo $NVM_DIR && nvm install --lts=dubnium