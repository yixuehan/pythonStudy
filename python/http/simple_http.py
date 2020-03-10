#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os, sys, platform
import BaseHTTPServer
from SocketServer import ThreadingMixIn
import threading
import urllib, urllib2
import shutil
import re
import time
try:
  from cStringIO import StringIO
except ImportError:
  from StringIO import StringIO
 
########################################################################################################
#   Overload and Impl the HttpRequest Handler.
########################################################################################################
class SimpleHTTPRequestHandler(BaseHTTPServer.BaseHTTPRequestHandler):
  #[GET]
  def do_GET(self):
    f = StringIO()
    f.write(self.path)
    length = f.tell()
    f.seek(0)
    self.response(length)
    if f:
      shutil.copyfileobj(f, self.wfile)
      f.close()
  #[Response]
  def response(self,length):
      self.send_response(200)
      self.send_header("Content-type", "text/html")
      self.send_header("Content-Length", str(length))
      self.end_headers()
 
########################################################################################################
#   Main Function
########################################################################################################
class ThreadingServer(ThreadingMixIn, BaseHTTPServer.HTTPServer):
  pass
if __name__ == '__main__':
  serveraddr = ('',int(sys.argv[1]))
  print "Listening Port(%s)" % (int(sys.argv[1]))
  srvr = ThreadingServer(serveraddr, SimpleHTTPRequestHandler)
  srvr.serve_forever()
