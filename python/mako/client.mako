#pragma once
#include <nlohmann/json.hpp>

<%
##(service_request, service_name)
    services = [('request','api'),('new_project','create_project'),('new_job','create_job'),('request','api2')]
%>


class ${module_name}
{
public:
% for service_request, service_name in services:
    void send(struct ${service_request} request)
    {   
        nlomann::json j = request;
        j['service_name'] = "${service_name}";
        send(j);
    }

% endfor
};
