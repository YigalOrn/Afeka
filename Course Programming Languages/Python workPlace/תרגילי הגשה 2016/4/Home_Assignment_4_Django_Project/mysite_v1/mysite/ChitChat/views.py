from django.shortcuts import render
from django.http import HttpResponseRedirect
from django.core.urlresolvers import reverse
from django.contrib.auth.decorators import login_required
from django.contrib.auth.forms import UserCreationForm
from django.contrib.auth.models import User
from django.contrib.auth import login
from django.db.models import Q
from .models import Message
from django.utils import timezone


# Create your views here.

@login_required
def index(request):
    userLst = User.objects.exclude(pk=request.user.pk)
    context = {'userLst': userLst}
    return render(request, 'ChitChat/index.html', context)


def userRegistration(request):
    form = UserCreationForm(request.POST)
    if form.is_valid():
        user = User.objects.create_user(
            username=request.POST['username'], password=request.POST['password1'])
        login(request, user)
        return HttpResponseRedirect(reverse('index'))
    return render(request, 'ChitChat/registration/userRegistration.html', {'form': form})


@login_required
def correspondence(request, user_pk):
    user_1, user_2 = User.objects.get(pk=request.user.pk), User.objects.get(pk=user_pk)
    messagesLst = list(
        Message.objects.filter(Q(sender=user_1, recipient=user_2) | Q(sender=user_2, recipient=user_1)))
    messagesLst.sort()
    registredUserLst = User.objects.exclude(pk=request.user.pk)
    return render(request, 'ChitChat/correspondence.html',
                  {'messagesLst': messagesLst, 'redirect_user': user_2})


@login_required
def newMessage(request, redirect_user_pk):
    sender = request.user
    recipient = User.objects.get(pk=redirect_user_pk)
    newMesage = Message(sender=sender, recipient=recipient,
                        message=request.POST['correspondence_textarea_form'],
                        pub_date=timezone.now())
    newMesage.save()
    return HttpResponseRedirect(reverse('correspondence', args=(redirect_user_pk,)))
