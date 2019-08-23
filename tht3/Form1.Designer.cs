namespace tht3 {
    partial class Form1 {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.labelGameTitle = new System.Windows.Forms.Label();
            this.labelSelectNumber = new System.Windows.Forms.Label();
            this.buttonCheck = new System.Windows.Forms.Button();
            this.numericUpDownUserValue = new System.Windows.Forms.NumericUpDown();
            this.labelResultMessage = new System.Windows.Forms.Label();
            this.labelCorrectGuesses = new System.Windows.Forms.Label();
            this.labelIncorrectGuesses = new System.Windows.Forms.Label();
            this.textBoxCorrectGuesses = new System.Windows.Forms.TextBox();
            this.textBoxIncorrectGuesses = new System.Windows.Forms.TextBox();
            this.radioButtonYes = new System.Windows.Forms.RadioButton();
            this.radioButtonNo = new System.Windows.Forms.RadioButton();
            this.groupBoxYesOrNo = new System.Windows.Forms.GroupBox();
            this.labelGameImage = new System.Windows.Forms.Label();
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownUserValue)).BeginInit();
            this.groupBoxYesOrNo.SuspendLayout();
            this.SuspendLayout();
            // 
            // labelGameTitle
            // 
            this.labelGameTitle.AutoSize = true;
            this.labelGameTitle.Font = new System.Drawing.Font("Microsoft Sans Serif", 21.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelGameTitle.ForeColor = System.Drawing.Color.Red;
            this.labelGameTitle.Location = new System.Drawing.Point(151, 9);
            this.labelGameTitle.Name = "labelGameTitle";
            this.labelGameTitle.Size = new System.Drawing.Size(387, 33);
            this.labelGameTitle.TabIndex = 0;
            this.labelGameTitle.Text = " ? WHAT\'S MY NUMBER ?";
            // 
            // labelSelectNumber
            // 
            this.labelSelectNumber.AutoSize = true;
            this.labelSelectNumber.BackColor = System.Drawing.Color.Transparent;
            this.labelSelectNumber.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelSelectNumber.Location = new System.Drawing.Point(24, 65);
            this.labelSelectNumber.Name = "labelSelectNumber";
            this.labelSelectNumber.Size = new System.Drawing.Size(384, 29);
            this.labelSelectNumber.TabIndex = 1;
            this.labelSelectNumber.Text = "Select a number between 1 and 10";
            // 
            // buttonCheck
            // 
            this.buttonCheck.BackColor = System.Drawing.Color.Red;
            this.buttonCheck.Enabled = false;
            this.buttonCheck.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.buttonCheck.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonCheck.Location = new System.Drawing.Point(540, 61);
            this.buttonCheck.Name = "buttonCheck";
            this.buttonCheck.Size = new System.Drawing.Size(99, 39);
            this.buttonCheck.TabIndex = 2;
            this.buttonCheck.Text = "CHECK";
            this.buttonCheck.UseVisualStyleBackColor = false;
            this.buttonCheck.Click += new System.EventHandler(this.buttonCheck_Click);
            // 
            // numericUpDownUserValue
            // 
            this.numericUpDownUserValue.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.numericUpDownUserValue.Location = new System.Drawing.Point(441, 65);
            this.numericUpDownUserValue.Maximum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.numericUpDownUserValue.Name = "numericUpDownUserValue";
            this.numericUpDownUserValue.ReadOnly = true;
            this.numericUpDownUserValue.Size = new System.Drawing.Size(50, 31);
            this.numericUpDownUserValue.TabIndex = 3;
            this.numericUpDownUserValue.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.numericUpDownUserValue.ValueChanged += new System.EventHandler(this.numericUpDownUserValue_ValueChanged);
            // 
            // labelResultMessage
            // 
            this.labelResultMessage.BackColor = System.Drawing.SystemColors.ControlLight;
            this.labelResultMessage.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.labelResultMessage.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelResultMessage.ForeColor = System.Drawing.SystemColors.ButtonShadow;
            this.labelResultMessage.Location = new System.Drawing.Point(181, 299);
            this.labelResultMessage.Name = "labelResultMessage";
            this.labelResultMessage.Size = new System.Drawing.Size(357, 27);
            this.labelResultMessage.TabIndex = 4;
            this.labelResultMessage.Text = "Result...";
            this.labelResultMessage.Visible = false;
            // 
            // labelCorrectGuesses
            // 
            this.labelCorrectGuesses.AutoSize = true;
            this.labelCorrectGuesses.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelCorrectGuesses.Location = new System.Drawing.Point(24, 344);
            this.labelCorrectGuesses.Name = "labelCorrectGuesses";
            this.labelCorrectGuesses.Size = new System.Drawing.Size(179, 25);
            this.labelCorrectGuesses.TabIndex = 5;
            this.labelCorrectGuesses.Text = "Correct Guesses:";
            // 
            // labelIncorrectGuesses
            // 
            this.labelIncorrectGuesses.AutoSize = true;
            this.labelIncorrectGuesses.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelIncorrectGuesses.Location = new System.Drawing.Point(323, 344);
            this.labelIncorrectGuesses.Name = "labelIncorrectGuesses";
            this.labelIncorrectGuesses.Size = new System.Drawing.Size(192, 25);
            this.labelIncorrectGuesses.TabIndex = 6;
            this.labelIncorrectGuesses.Text = "Incorrect Guesses:";
            // 
            // textBoxCorrectGuesses
            // 
            this.textBoxCorrectGuesses.BackColor = System.Drawing.Color.OliveDrab;
            this.textBoxCorrectGuesses.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBoxCorrectGuesses.Location = new System.Drawing.Point(233, 344);
            this.textBoxCorrectGuesses.Name = "textBoxCorrectGuesses";
            this.textBoxCorrectGuesses.ReadOnly = true;
            this.textBoxCorrectGuesses.Size = new System.Drawing.Size(46, 31);
            this.textBoxCorrectGuesses.TabIndex = 7;
            this.textBoxCorrectGuesses.Text = "0";
            this.textBoxCorrectGuesses.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // textBoxIncorrectGuesses
            // 
            this.textBoxIncorrectGuesses.BackColor = System.Drawing.Color.Tomato;
            this.textBoxIncorrectGuesses.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBoxIncorrectGuesses.Location = new System.Drawing.Point(565, 341);
            this.textBoxIncorrectGuesses.Name = "textBoxIncorrectGuesses";
            this.textBoxIncorrectGuesses.ReadOnly = true;
            this.textBoxIncorrectGuesses.Size = new System.Drawing.Size(44, 31);
            this.textBoxIncorrectGuesses.TabIndex = 8;
            this.textBoxIncorrectGuesses.Text = "0";
            this.textBoxIncorrectGuesses.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // radioButtonYes
            // 
            this.radioButtonYes.AutoSize = true;
            this.radioButtonYes.Location = new System.Drawing.Point(17, 38);
            this.radioButtonYes.Name = "radioButtonYes";
            this.radioButtonYes.Size = new System.Drawing.Size(68, 29);
            this.radioButtonYes.TabIndex = 9;
            this.radioButtonYes.TabStop = true;
            this.radioButtonYes.Text = "Yes";
            this.radioButtonYes.UseVisualStyleBackColor = true;
            this.radioButtonYes.CheckedChanged += new System.EventHandler(this.radioButtonYes_CheckedChanged);
            // 
            // radioButtonNo
            // 
            this.radioButtonNo.AutoSize = true;
            this.radioButtonNo.Location = new System.Drawing.Point(108, 38);
            this.radioButtonNo.Name = "radioButtonNo";
            this.radioButtonNo.Size = new System.Drawing.Size(57, 29);
            this.radioButtonNo.TabIndex = 10;
            this.radioButtonNo.TabStop = true;
            this.radioButtonNo.Text = "No";
            this.radioButtonNo.UseVisualStyleBackColor = true;
            this.radioButtonNo.CheckedChanged += new System.EventHandler(this.radioButtonNo_CheckedChanged);
            // 
            // groupBoxYesOrNo
            // 
            this.groupBoxYesOrNo.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(255)))));
            this.groupBoxYesOrNo.Controls.Add(this.radioButtonYes);
            this.groupBoxYesOrNo.Controls.Add(this.radioButtonNo);
            this.groupBoxYesOrNo.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBoxYesOrNo.Location = new System.Drawing.Point(266, 396);
            this.groupBoxYesOrNo.Name = "groupBoxYesOrNo";
            this.groupBoxYesOrNo.Size = new System.Drawing.Size(249, 79);
            this.groupBoxYesOrNo.TabIndex = 11;
            this.groupBoxYesOrNo.TabStop = false;
            this.groupBoxYesOrNo.Text = "Another guess?";
            this.groupBoxYesOrNo.Visible = false;
            // 
            // labelGameImage
            // 
            this.labelGameImage.Font = new System.Drawing.Font("Microsoft Sans Serif", 69.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelGameImage.Image = ((System.Drawing.Image)(resources.GetObject("labelGameImage.Image")));
            this.labelGameImage.Location = new System.Drawing.Point(248, 109);
            this.labelGameImage.Name = "labelGameImage";
            this.labelGameImage.Size = new System.Drawing.Size(219, 174);
            this.labelGameImage.TabIndex = 12;
            this.labelGameImage.Text = "       \r\n\r\n";
            // 
            // imageList1
            // 
            this.imageList1.ColorDepth = System.Windows.Forms.ColorDepth.Depth8Bit;
            this.imageList1.ImageSize = new System.Drawing.Size(16, 16);
            this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(255)))));
            this.ClientSize = new System.Drawing.Size(696, 487);
            this.Controls.Add(this.labelGameImage);
            this.Controls.Add(this.groupBoxYesOrNo);
            this.Controls.Add(this.textBoxIncorrectGuesses);
            this.Controls.Add(this.textBoxCorrectGuesses);
            this.Controls.Add(this.labelIncorrectGuesses);
            this.Controls.Add(this.labelCorrectGuesses);
            this.Controls.Add(this.labelResultMessage);
            this.Controls.Add(this.numericUpDownUserValue);
            this.Controls.Add(this.buttonCheck);
            this.Controls.Add(this.labelSelectNumber);
            this.Controls.Add(this.labelGameTitle);
            this.Cursor = System.Windows.Forms.Cursors.Hand;
            this.Name = "Form1";
            this.Text = "Guessing Game                                       ";
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownUserValue)).EndInit();
            this.groupBoxYesOrNo.ResumeLayout(false);
            this.groupBoxYesOrNo.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label labelGameTitle;
        private System.Windows.Forms.Label labelSelectNumber;
        private System.Windows.Forms.Button buttonCheck;
        private System.Windows.Forms.NumericUpDown numericUpDownUserValue;
        private System.Windows.Forms.Label labelResultMessage;
        private System.Windows.Forms.Label labelCorrectGuesses;
        private System.Windows.Forms.Label labelIncorrectGuesses;
        private System.Windows.Forms.TextBox textBoxCorrectGuesses;
        private System.Windows.Forms.TextBox textBoxIncorrectGuesses;
        private System.Windows.Forms.RadioButton radioButtonYes;
        private System.Windows.Forms.RadioButton radioButtonNo;
        private System.Windows.Forms.GroupBox groupBoxYesOrNo;
        private System.Windows.Forms.Label labelGameImage;
        private System.Windows.Forms.ImageList imageList1;
    }
}

