from django.db import models
from django.contrib.auth.models import User


# Create your models here.

class Message(models.Model):
    sender = models.ForeignKey(User, related_name='sender_set', on_delete=models.CASCADE)
    recipient = models.ForeignKey(User, related_name='recipient_set', on_delete=models.CASCADE)
    message = models.CharField(max_length=500)
    pub_date = models.DateTimeField('date published')

    def __str__(self):
        return str(self.message)
