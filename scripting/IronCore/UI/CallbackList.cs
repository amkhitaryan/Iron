﻿using System.Collections.Generic;

namespace Iron
{
    /// <summary>
    /// List of callbacks to be called
    /// </summary>
    public class CallbackList
    {
        private readonly List<CallbackWrapper> callbackList = new List<CallbackWrapper>();
        internal bool IsActive = true;

        /// <summary>
        /// Registers new event callback
        /// </summary>
        /// <param name="action">Callback</param>
        public void AddCallback(CallbackAction action)
        {
            callbackList.Add(new CallbackWrapper(action));
        }

        /// <summary>
        /// Removes already registered callback
        /// </summary>
        /// <param name="action">Callback</param>
        public void RemoveCallback(CallbackAction action)
        {
            callbackList.Remove(new CallbackWrapper(action));
        }
        
        /// <summary>
        /// Removes all registered callbacks
        /// </summary>
        public void ClearCallbacks()
        {
            callbackList.Clear();
        }

        /// <summary>
        /// Calls all registered callbacks
        /// </summary>
        public void Invoke()
        {
            if (!IsActive)
                return;
            
            foreach (CallbackWrapper callbackWrapper in callbackList)
            {
                callbackWrapper.Invoke();
            }
        }
    }
}