#include "UI/CLView.hpp"
#include "assets.hpp"
using namespace ChatLib::UI;
DEFINE_TYPE(ChatLib::UI, CLView);

#include "UnityEngine/Application.hpp"
#include "bsml/shared/BSML.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void CLView::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
{
    if (!firstActivation)
        return;

    BSML::parse_and_construct(IncludedAssets::main_bsml, get_transform(), this);
}

void CLView::PostParse()
{
    ifaddrs *ifap, *ifa;
    getifaddrs(&ifap);

    for (ifa = ifap; ifa != nullptr; ifa = ifa->ifa_next)
    {
        sockaddr_in *addr = (sockaddr_in*) ifa->ifa_addr;
        if (strcmp(ifa->ifa_name, "wlan0") == 0)
        {
            const char* ip = inet_ntoa(addr->sin_addr);
            IPText->SetText("Accessing Via Phone/PC: <color=#2a9c2c>http://" + static_cast<std::string>(ip) + ":50009</color>");
        }
    }
}

void CLView::OpenIPWebpage()
{
    UnityEngine::Application::OpenURL("http://localhost:50009");
}