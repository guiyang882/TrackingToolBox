#-*- coding : utf-8 -*-

import sys
import os
import time

def permission_check(user):
    if user.is_authenticated():
        return True
    else:
        return False
