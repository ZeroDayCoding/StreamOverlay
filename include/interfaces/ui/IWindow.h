#ifndef __IWINDOW_H__
#define __IWINDOW_H__
#include "interfaces/IBase.h"

__NAMESPACE_GUARD_BEGIN(ZDC)
__NAMESPACE_GUARD_BEGIN(StreamOverlay)
__NAMESPACE_GUARD_BEGIN(Interfaces)
__NAMESPACE_GUARD_BEGIN(UI)
__EXTERN_C_GUARD_BEGIN

DECLARE_INTERFACE IWindow
INTERFACE_INHERITS_FROM(IBase)
{
public:
    DECLARE_INTERFACE_VFTABLE_(IBase)
    /**
     * @brief Creates a graphical window, may be either virtual or monitor-backed depending on factory.
     * @param strTitle The initial title of the window, may be nullptr for default name.
     * @param nX The initial x position of the window, use zero for left-most of main monitor.
     * @param nY The initial y position of the window, use zero for top-most of main monitor.
     * @param nWidth The initial width of the window, this should be a positive non-zero number.
     * @param nHeight The initial height of the window, this should be a positive non-zero number.
     * @param bShow Allows the caller to immediately show the window when set to True, or delay showing until a later SetVisible call using False.
     * @returns True if the window was successfully created, otherwise False.
     */
    DECLARE_INTERFACE_VFUNCTION(Create, bool_t)(IThis_ const char* strTitle, s32_t nX, s32_t nY, s32_t nWidth, s32_t nHeight, bool_t bShow) PURE;
    /**
     * @brief Sets the title of the window, or remove the title.
     * @param strTitle The desired title of the window, may be nullptr if the title should be removed.
     * @returns True if the window's title was updated, otherwise False.
     */
    DECLARE_INTERFACE_VFUNCTION(SetTitle, bool_t)(IThis_ const char* strTitle);
    /**
     * @brief Sets the window's visibility.
     * @note This function doesn't minimize or hide the window, instead it stops displaying it and hides the windows existance from the user (aka not on user dashboard/taskbar).
     * @param bVisible True if the window should become visible to the user, otherwise False.
     * @param pbWasVisible An optional pointer to a boolean value that will be set to the previous visibilty state's value.
     * @returns True if the window's visibility was changed, otherwise False.
     */
    DECLARE_INTERFACE_VFUNCTION(SetVisible, bool_t)(IThis_ bool_t bVisible, bool_t* pbWasVisible) PURE;
    /**
     * @brief Sets the window's top-left coordinates position.
     * @param nX The desired x value of the window.
     * @param nY The desired y value of the window.
     * @returns True if the window was moved, otherwise False. 
     */
    DECLARE_INTERFACE_VFUNCTION(SetPosition, bool_t)(IThis_ s32_t nX, s32_t nY) PURE;
    /**
     * @brief Sets the window's dimensions.
     * @note If the window has a border the borders thickness is assumed to be accounted in the dimensions.
     * @param nWidth The desired width value for the window.
     * @param nHeight The desired height value for the window.
     * @returns True if the window was resized, otherwise False. 
     */
    DECLARE_INTERFACE_VFUNCTION(SetDimensions, bool_t)(IThis_ s32_t nWidth, s32_t nHeight) PURE;
    DELCARE_INTERFACE_VFTABLE_END
};

__EXTERN_C_GUARD_END
__NAMESPACE_GUARD_END
__NAMESPACE_GUARD_END
__NAMESPACE_GUARD_END
__NAMESPACE_GUARD_END
#endif//__IWINDOW_H__ GUARD