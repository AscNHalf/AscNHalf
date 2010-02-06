SET(event_SRCS
   EventScripts/Event_DarkPortal.cpp
   EventScripts/Event_DarkPortal.h
   EventScripts/Halloween.cpp
   EventScripts/WinterVeil.cpp
   EventScripts/Setup.cpp
   EventScripts/Setup.h
   Common/Base.cpp
   Common/Base.h
   Common/EasyFunctions.h
   Common/Instance_Base.cpp
   Common/Instance_Base.h
)

add_library(event ${event_SRCS})
