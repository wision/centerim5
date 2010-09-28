# When you add files here, also add them in po/POTFILES.in
set( centerim_SOURCES
	AccountStatusMenu.cpp
	AccountWindow.cpp
	Accounts.cpp
	BuddyList.cpp
	BuddyListNode.cpp
	CenterIM.cpp
	CenterMain.cpp
	Conf.cpp
	Conversation.cpp
	Conversations.cpp
	Connections.cpp
	GeneralMenu.cpp
	Header.cpp
	Log.cpp
	Notify.cpp
	Request.cpp
	Transfers.cpp
	Utils.cpp
	git-version.cpp
)

set( centerim_HEADERS
	AccountStatusMenu.h
	AccountWindow.h
	Accounts.h
	BuddyList.h
	BuddyListNode.h
	CenterIM.h
	CenterMain.h
	Conf.h
	Conversation.h
	Conversations.h
	Connections.h
	Defines.h
	GeneralMenu.h
	Header.h
	Log.h
	Notify.h
	Request.h
	Transfers.h
	Utils.h
	git-version.h.in
)

include_directories( ${centerim_BINARY_DIR}/src/)

add_custom_target( git-version.h ALL
			COMMAND		${centerim_SOURCE_DIR}/misc/git-version-gen ${centerim_SOURCE_DIR}/.version git-version || echo "GIT version updated successfully"
			COMMAND		sed -e s/"@GIT_VERSION@"/`cat git-version`/g < ${CMAKE_CURRENT_SOURCE_DIR}/git-version.h.in > git-version.h
			COMMAND		${CMAKE_COMMAND} -E remove git-version
		)

add_executable( centerim
		${centerim_SOURCES}
		${centerim_HEADERS}
	)

add_dependencies( centerim git-version.h )

target_link_libraries( centerim
		termkey
		cppconsui
		${PURPLE_LIBRARIES}
	)