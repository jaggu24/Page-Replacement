
#!/usr/bin/perl 
  
# Opening a File in Read-only mode 
open(r, "<", "output.txt"); 
  
# Printing content of the File 
print(<r>); 
  
# Closing the File 
close(r); 

