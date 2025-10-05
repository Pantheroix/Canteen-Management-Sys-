#To compile (GTK 4):
gcc App.c -o app $(pkg-config --cflags --libs gtk4)

step2:
./app to run
Tested with MSYS2 (ucrt64)



How to Contribute:-

Create a Issue with Detail on how are you going to change it .

Create your fork.

Keep your fork updated.

3. Create a New Branch:
   
  git checkout -b your-branch-name

5. Make Your Changes:
7. Commit Your Changes:
   
git add .

git commit -m "Describe your changes"

9. Push to the Branch:
    
git push origin your-branch-name

11. Create a Pull Request:
    
Go to the original repository and click New Pull Request.

Keeping Your Fork Updated

Before making a pull request, ensure that your forked repository is up to date.

Add Remote Upstream:

git remote add upstream https://github.com/Pantheroix/Canteen-Management-Sys-.git

Fetch Upstream Changes:

git fetch upstream

Merge Changes into Main:

git checkout main

git merge upstream/main

Push Changes to Your Fork:

git push origin main

By following these steps, your pull request will be based on the latest code.
