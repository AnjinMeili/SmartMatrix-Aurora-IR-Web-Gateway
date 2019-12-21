#!/usr/bin/gawk -f
# 
# Quick and dirty script to read Aurora's ircodes.h and dump a control block for esp8266.
# First pass at getting a diagnostic block with every acceptable IR code Aurora understands.
# 
# $ make_ir_html.awk ircodes.h
# 

/\#define/{
	if(NF>2){
		IRcodes[$2] = $NF;
		}
	}
/case/{
	code = substr($2,1,length($2)-1);
	}
/return/{
	split($2,tary,":");
	cmd = tary[3];
	Command[code] = substr(cmd,1,length(cmd)-1);;
	}
END{
	for(idx in IRcodes){
		name = idx ;
		gsub("IRCODE_","",name);	
		if(index(idx,"SMARTMATRIX")){
	                printf "                  \042<p><a href=\\\042ir?code=%s\\\042>%s - %s - Send 0x%08X</a></p>\042 \\\n",
				IRcodes[idx],name,Command[idx],IRcodes[idx]
			}
		}	
	for(idx in IRcodes){
		name = idx ;
		gsub("IRCODE_","",name);	
		if(index(idx,"ADAFRUIT")){
	                printf "                  \042<p><a href=\\\042ir?code=%s\\\042>%s - %s - Send 0x%08X</a></p>\042 \\\n",
				IRcodes[idx],name,Command[idx],IRcodes[idx]
			}
		}	
	for(idx in IRcodes){
		name = idx ;
		gsub("IRCODE_","",name);	
		if(index(idx,"SPARKFUN")){
	                printf "                  \042<p><a href=\\\042ir?code=%s\\\042>%s - %s - Send 0x%08X</a></p>\042 \\\n",
				IRcodes[idx],name,Command[idx],IRcodes[idx]
			}
		}	
	for(idx in IRcodes){
		name = idx ;
		gsub("IRCODE_","",name);	
		if(index(idx,"RONIX")){
	                printf "                  \042<p><a href=\\\042ir?code=%s\\\042>%s - %s - Send 0x%08X</a></p>\042 \\\n",
				IRcodes[idx],name,Command[idx],IRcodes[idx]
			}
		}	
	}
