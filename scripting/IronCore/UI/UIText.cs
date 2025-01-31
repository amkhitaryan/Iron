﻿using System.Runtime.CompilerServices;
using System.Text;

namespace Iron
{
    /// <summary>
    /// UI text
    /// </summary>
    public class UIText : UIComponent
    {
        /// <summary>
        /// Text
        /// </summary>
        public string Text
        {
            get => GetText_Internal(Entity.ID);
            set => SetText_Internal(Entity.ID, Encoding.UTF8.GetString(Encoding.Default.GetBytes(value)));
        }
        
        /// <summary>
        /// Text font size in pixels
        /// </summary>
        public int TextSize
        {
            get => GetTextSize_Internal(Entity.ID);
            set => SetTextSize_Internal(Entity.ID, value);
        }
        
        /// <summary>
        /// Text color
        /// </summary>
        public Color Color
        {
            get => GetColor_Internal(Entity.ID);
            set => SetColor_Internal(Entity.ID, value);
        }
        
        /// <summary>
        /// Should text size change automatically to fit in the rect
        /// </summary>
        public bool IsTextAutoSize
        {
            get => GetIsTextAutoSize_Internal(Entity.ID);
            set => SetIsTextAutoSize_Internal(Entity.ID, value);
        }
        
        /// <summary>
        /// How text should position itself in the rect
        /// </summary>
        public AlignmentType TextAlignment
        {
            get => GetTextAlignment_Internal(Entity.ID);
            set => SetTextAlignment_Internal(Entity.ID, value);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern string GetText_Internal(uint entityID);
        
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void SetText_Internal(uint entityID, string text);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern int GetTextSize_Internal(uint entityID);
        
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void SetTextSize_Internal(uint entityID, int textSize);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern Color GetColor_Internal(uint entityID);
        
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void SetColor_Internal(uint entityID, Color color);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern bool GetIsTextAutoSize_Internal(uint entityID);
        
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void SetIsTextAutoSize_Internal(uint entityID, bool isAutoSize);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern AlignmentType GetTextAlignment_Internal(uint entityID);
        
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void SetTextAlignment_Internal(uint entityID, AlignmentType alignmentType);
    }
}