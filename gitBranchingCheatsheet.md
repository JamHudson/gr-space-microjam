# Git Branching Cheatsheet

A few quick recipes for working with git branches and upstreams.

This assumes you have already added an upstream and are MAKING ALL CHANGES ON BRANCHES OTHER THAN MAIN.

## Pulling from upstream and updating branches
The following steps are done by ONLY ONE PARTNER.
1. If you have uncommited changes on your branch (e.g. dev), commit and push those before continuing. You can check with `git status`. Make sure you're not accidentally committing to main!
1. Switch to the main branch: `git switch main`
1. Pull from the upstream: `git pull upstream main` So long as you have not been committing anything directly to main, this should be a fast-forward and there will be no merge conflicts.
1. Push main back to your fork: `git push origin main`
1. Switch to the branch you are working on (e.g. dev)
1. Merge your main branch into your working branch: `git merge main` There may be a merge message that pops up in VS Code you can confirm, or there may be merge conflicts you need to resolve. Resolve them and commit as necessary.
1. Push your updated branch to your fork: `git push origin`
1. Now, all of the other partners can pull down the merged changes on each branch: `git pull`

