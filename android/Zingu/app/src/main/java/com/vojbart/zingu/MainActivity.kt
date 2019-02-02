package com.vojbart.zingu

import android.graphics.Color
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import kotlinx.android.synthetic.main.activity_main.*
import android.content.DialogInterface
import android.bluetooth.BluetoothAdapter
import android.support.v7.app.AlertDialog
import android.content.Intent


class MainActivity : AppCompatActivity() {
    var REQUEST_BLUETOOTH = 1
    lateinit var bluetoothCom: BluetoothCom
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        window.navigationBarColor = Color.TRANSPARENT

        val BTAdapter = BluetoothAdapter.getDefaultAdapter()
        bluetoothCom = BluetoothCom(this)
        if (!BTAdapter.isEnabled) {
            val enableBT = Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE)
            startActivityForResult(enableBT, REQUEST_BLUETOOTH)
        }

        button_drive.setOnClickListener {
            bluetoothCom.write("drive")
        }
        image_bluetooth.setOnClickListener {

            // Phone does not support Bluetooth so let the user know and exit.
            if (BTAdapter == null) {
                AlertDialog.Builder(this)
                        .setTitle("Not compatible")
                        .setMessage("Your phone does not support Bluetooth")
                        .setPositiveButton("Exit") { _, _ -> System.exit(0) }
                        .setIcon(android.R.drawable.ic_dialog_alert)
                        .show()
            }

            bluetoothCom.showDeviceListDialog()


        }
    }
}
