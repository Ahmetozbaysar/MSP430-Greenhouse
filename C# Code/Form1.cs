using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using RestSharp;
using System.IO.Ports;

namespace MSP430_Project
{
    public partial class Form1 : Form
    {
        string[] portlar = SerialPort.GetPortNames();
        SerialPort portum = new System.IO.Ports.SerialPort();
        //public int a2;

        public Form1()
        {
            InitializeComponent();
            
        }

        public int i = 0;

        private void button1_Click(object sender, EventArgs e)
        {

            if (portum.IsOpen == false)
            {

                if (comboBox1.Text == "")
                    return;
                portum.BaudRate = 19200;
                portum.PortName = comboBox1.SelectedItem.ToString();
                try
                {
                    portum.Open();
                    label7.Text = "Port is open";
                }
                catch (Exception hata)
                {
                    MessageBox.Show(hata.Message);

                }
            }
            else
            {
                label7.Text = "Connected";
               
            }


            timer1.Start();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            

        groupBox5.Enabled = false;
            groupBox4.Enabled = false;
            groupBox3.Enabled = false;
            groupBox2.Enabled = false;
            groupBox1.Enabled = false;

            


            string[] Portlar = SerialPort.GetPortNames();
            foreach (string port in Portlar)
            {
                comboBox1.Items.Add(port);
            }

        }

        private void button2_Click(object sender, EventArgs e)
        {
            groupBox5.Enabled = false;
            groupBox4.Enabled = false;
            groupBox3.Enabled = false;
            groupBox2.Enabled = false;
            groupBox1.Enabled = false;

            timer1.Stop();
            if (portum.IsOpen == true)
            {
                portum.Close();
                label7.Text = "Port is closed";
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            portum.Write("D");

            // timer2.Enabled=true;
            // timer2.Enabled = false;
            System.Threading.Thread.Sleep(2000);
            portum.Write("R");

        }

        private void button4_Click(object sender, EventArgs e)
        {
            portum.Write("E");
            timer1.Enabled = false;
            System.Threading.Thread.Sleep(6000);
            timer1.Enabled = true;
            portum.Write("R");

        }

        private void timer1_Tick_1(object sender, EventArgs e)
        {
            if (portum.IsOpen == true)
            {
                groupBox5.Enabled = true;
                groupBox4.Enabled = true;
                groupBox3.Enabled = true;
                groupBox2.Enabled = true;
                groupBox1.Enabled = true;
            }
                try
                {
                    string sonuc = portum.ReadExisting();
                    string[] sonuclar = sonuc.Split(" ");


                // string nem = sonuclar[0];
                //string isik = sonuclar[1] ;
                //foreach (string son in sonuclar)

                // int isik = Int32.Parse(sonuclar[0]);

                int a0 = (1023 - (Convert.ToInt32(sonuclar[0]))) * 100 / 1023;
                int a1 = ((Convert.ToInt32(sonuclar[3]))) / 10;
                float a2 = (1023 - (Convert.ToInt32(sonuclar[4]))) * 100 / 1023;
                // label4.Text = sonuc;
                label4.Text = a2.ToString();
                label6.Text = a1.ToString();
                label2.Text = a0.ToString();
                //label4.Text = sonuclar[3];
                //label6.Text = sonuclar[4];
            }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                    
                //throw;
                }
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (portum.IsOpen == true)
            {
                portum.Close();
                label7.Text = "Port is closed";
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            portum.Write("F");
        }

        private void iyabtn_Click(object sender, EventArgs e)
        {
            portum.Write("J");
        }

        private void sdabtn_Click(object sender, EventArgs e)
        {
            portum.Write("A");
            //System.Threading.Thread.Sleep(2000);
           // portum.Write("E");
        }

        private void fcabtn_Click(object sender, EventArgs e)
        {
            portum.Write("G");
        }

        private void fcobtn_Click(object sender, EventArgs e)
        {
            portum.Write("H");
        }

        private void fccbtn_Click(object sender, EventArgs e)
        {
            portum.Write("I");
        }

        private void iyobtn_Click(object sender, EventArgs e)
        {
            portum.Write("K");
        }

        private void iycbtn_Click(object sender, EventArgs e)
        {
            portum.Write("L");
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
        }
        private void sdobtn_Click(object sender, EventArgs e)
        {
            portum.Write("B");
        }

        private void sdcbtn_Click(object sender, EventArgs e)
        {
            portum.Write("C");
        }

        private void iabtn_Click(object sender, EventArgs e)
        {
            portum.Write("M");
        }

        private void ikbtn_Click(object sender, EventArgs e)
        {
            portum.Write("N");
        }


        private void button5_Click_1(object sender, EventArgs e)
        {
            portum.Write("O");
        }

        private void button6_Click(object sender, EventArgs e)
        {
            portum.Write("P");
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
           
            
        }
    }
}

