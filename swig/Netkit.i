%module Netkit

%{
#include "Attachment.h"
#include "Interface.h"
#include "Lab.h"
#include "Machine.h"
#include "Route.h"
#include "Rule.h"
%}

%include <std_string.i>
%include <std_vector.i>

%include "Attachment.h"
%include "Interface.h"
%include "Lab.h"
%include "Machine.h"
%include "Route.h"
%include "Rule.h"

%template(machinevec) std::vector<Machine>;